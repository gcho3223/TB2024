#include "header/SimplePlotTools.h"
#include "header/RunInfo.h"
#include "header/GausFitter.h"

class EMResolution {
public:
  EMResolution(TString inputPath, TString centerTowerTag): 
  inputPath_(inputPath), centerTowerTag_(centerTowerTag) { }

  void Set_PlotPath(TString path) { plotPath_ = path; }

  void NoFit(bool noFit=kTRUE) { noFit_ = noFit; }

  void Use_PartialTower(TString tag_partialTower) {
    use_partialTower_ = kTRUE;
    tag_partialTower_ = tag_partialTower;
    if( (tag_partialTower_ == "nearM8T2" && centerTowerTag_ != "M8-T2") || 
        (tag_partialTower_ == "nearM9T1" && centerTowerTag_ != "M9-T1") ||
        (tag_partialTower_ == "nearM5T1" && centerTowerTag_ != "M5-T1") ||
        (tag_partialTower_ == "nearM5T3" && centerTowerTag_ != "M5-T3") ) {
      printf("[EMResolution::Use_PartialTower] tag for partial tower is %s, but reference tower is %s!\n", tag_partialTower_.Data(), centerTowerTag_.Data());
      throw std::invalid_argument("tower inconsistency is found");
    }
  }

  void Produce() {
    Init();

    ProducePlot_PerPoint();
    ProducePlot_Resol_vs_E();
    ProducePlot_Linearity_vs_E();
  }

  void Produce(TString plotPath) {
    Set_PlotPath(plotPath);
    Produce();
  }

private:
  TString inputPath_;
  TString plotPath_ = "./";

  TString centerTowerTag_;
  std::vector<int> vec_run_;
  std::vector<double> vec_energy_;

  bool noFit_ = kFALSE; // -- default: do gaussian fit

  // -- when partial # towers are used, not full 3x3 modules
  bool use_partialTower_ = kFALSE;
  TString tag_partialTower_ = "undefined"; // -- tag for hist. name (e.g. "nearM8T2" if the hist. = h_eDep_nearM8T2_DWCPSMC)

  void Init() {
    vec_energy_ = TB2024::vec_emScanE;
    vec_run_ = TB2024::map_emScanRun[centerTowerTag_];

    int nPoint = (int)vec_energy_.size();
    vector<TString> vec_fiberType = {"C", "S", "Sum"};
    for(auto& fiberType : vec_fiberType ) {
      map_resol_.insert( std::make_pair(fiberType, new TGraphAsymmErrors(nPoint)) );
      map_linearity_.insert( std::make_pair(fiberType, new TGraphAsymmErrors(nPoint)) );
    }
  }

  std::map<TString, TGraphAsymmErrors*> map_resol_;
  std::map<TString, TGraphAsymmErrors*> map_linearity_;

  void ProducePlot_PerPoint() {
    int nPoint = (int)vec_energy_.size();
    for(int i=0; i<nPoint; ++i) {
      ProducePlot_PerPoint(i, vec_run_[i], vec_energy_[i], "C");
      ProducePlot_PerPoint(i, vec_run_[i], vec_energy_[i], "S");
      ProducePlot_PerPoint(i, vec_run_[i], vec_energy_[i], "Sum");
    }
  }

  void ProducePlot_Resol_vs_E() {
    TF1* resolFunc_C = new TF1("resolFunc_C", "TMath::Sqrt( ([0]/x)*([0]/x) + ([1]/TMath::Sqrt(x))*([1]/TMath::Sqrt(x))+[2]*[2] )", 0, 120);
    resolFunc_C->SetParameter(0, 1);
    resolFunc_C->SetParameter(1, 0.2);
    resolFunc_C->SetParameter(2, 0.05);
    // resolFunc_C->SetParLimits(1, 0, 1e10); // -- positive
    resolFunc_C->SetLineColor(kBlue);

    TF1* resolFunc_S = new TF1("resolFunc_S", "TMath::Sqrt( ([0]/x)*([0]/x) + ([1]/TMath::Sqrt(x))*([1]/TMath::Sqrt(x))+[2]*[2] )", 0, 120);
    resolFunc_S->SetParameter(0, 1);
    resolFunc_S->SetParameter(1, 0.2);
    resolFunc_S->SetParameter(2, 0.05);
    // resolFunc_S->SetParLimits(1, 0, 1e10); // -- positive
    resolFunc_S->SetLineColor(kRed);

    TF1* resolFunc_sum = new TF1("resolFunc_sum", "TMath::Sqrt( ([0]/x)*([0]/x) + ([1]/TMath::Sqrt(x))*([1]/TMath::Sqrt(x))+[2]*[2] )", 0, 120);
    resolFunc_sum->SetParameter(0, 1);
    resolFunc_sum->SetParameter(1, 0.2);
    resolFunc_sum->SetParameter(2, 0.05);
    // resolFunc_sum->SetParLimits(1, 0, 1e10); // -- positive
    resolFunc_sum->SetLineColor(kBlack);

    map_resol_["C"]->Fit("resolFunc_C");
    map_resol_["S"]->Fit("resolFunc_S");
    map_resol_["Sum"]->Fit("resolFunc_sum");


    TString canvasName = TString::Format("c_emResol_%s", centerTowerTag_.Data());
    PlotTool::GraphCanvas* canvas = new PlotTool::GraphCanvas(canvasName, 0, 0);
    canvas->SetTitle("E [GeV]", "#sigma/E");

    canvas->Register(map_resol_["C"],   MakeLegend_Resol("C",   resolFunc_C),   kBlue);
    canvas->Register(map_resol_["S"],   MakeLegend_Resol("S",   resolFunc_S),   kRed);
    canvas->Register(map_resol_["Sum"], MakeLegend_Resol("Sum", resolFunc_sum), kBlack);

    // canvas->SetMarkerSize(2.0);

    if( noFit_ ) canvas->SetLegendPosition(0.16, 0.14, 0.80, 0.35);
    else         canvas->SetLegendPosition(0.24, 0.65, 0.95, 0.91);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(0, 0.4);
    // canvas->SetAutoRangeY();

    // canvas->Latex_CMSInternal();
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    TString beamInfo = "e+ beam (10 - 100 GeV)";
    canvas->RegisterLatex(0.65, 0.96, 62, 0.6, beamInfo);

    TString centerInfo = "Center: "+centerTowerTag_;

    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, centerInfo);

    canvas->SetSavePath(plotPath_);
    canvas->Draw();
  }

  TString MakeLegend_Resol(TString fiberType, TF1* fitFunc) {
    TString legend = TString::Format("%s: %.3lf/E + %.3lf/#sqrt{E} + %.3lf (#chi2/nDOF = %.2lf/%d)", fiberType.Data(), 
      fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2), fitFunc->GetChisquare(), fitFunc->GetNDF());

    return legend;
  }

  void ProducePlot_Linearity_vs_E() {
    TString canvasName = TString::Format("c_linearity_%s", centerTowerTag_.Data());
    PlotTool::GraphCanvas* canvas = new PlotTool::GraphCanvas(canvasName, 0, 0);
    canvas->SetTitle("E [GeV]", "E_{measured}/E_{beam}");

    canvas->Register(map_linearity_["C"],   "C channel",   kBlue);
    canvas->Register(map_linearity_["S"],   "S channel",   kRed);
    canvas->Register(map_linearity_["Sum"], "C+S channel", kBlack);

    // canvas->SetMarkerSize(2.0);

    canvas->SetLegendPosition(0.50, 0.70, 0.95, 0.95);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(0.7, 1.5);
    // canvas->SetAutoRangeY();

    // canvas->Latex_CMSInternal();
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    TString beamInfo = "e+ beam (10 - 100 GeV)";
    canvas->RegisterLatex(0.65, 0.96, 62, 0.6, beamInfo);

    TString centerInfo = "Center: "+centerTowerTag_;

    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, centerInfo);

    canvas->SetSavePath(plotPath_);
    canvas->Draw();
    
  }

  void ProducePlot_PerPoint(int i_point, int run, double energy, TString fiberType) {
    TString fileName = Get_FileName(run);
    TString histName = "";
    if( fiberType == "Sum" ) histName = "h_eDep_all_DWCPSMC";
    else                     histName = TString::Format("h_eDep_all-%s_DWCPSMC", fiberType.Data());

    if( use_partialTower_ )
      histName.ReplaceAll("eDep_all", "eDep_"+tag_partialTower_);

    TH1D* h_eDep = PlotTool::Get_Hist(fileName, histName);
    Double_t nEvent = h_eDep->Integral();
    cout << "(energy, fiber) = (" << energy << ", " << fiberType << "): # events = " << nEvent << endl;

    // -- from histogram values (no fit)
    double mean   = h_eDep->GetMean();
    double stdDev = h_eDep->GetStdDev();
    double resol = stdDev / mean;
    double absUnc_mean   = h_eDep->GetMeanError();
    double absUnc_stdDev = h_eDep->GetStdDevError();
    double absUnc_resol  = AbsUnc_AoverB(stdDev, absUnc_stdDev, mean, absUnc_mean);

    // -- fit
    GausFitter fitter(h_eDep);
    if( !noFit_ ) {
      if( fiberType == "Sum" ) fitter.SetColor(kBlue);
      fitter.Fit();
    }

    TString canvasName = TString::Format("eDep_%s_energy%.0lf_run%d", fiberType.Data(), energy, run);
    if( use_partialTower_ )
      canvasName.ReplaceAll("eDep", "eDep_"+tag_partialTower_);

    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Energy deposit [GeV]", "# events");

    int color;
    if( fiberType == "C" ) color = kBlue;
    if( fiberType == "S" ) color = kRed;
    if( fiberType == "Sum" ) color = kBlack;

    canvas->Register(h_eDep, "", color);

    canvas->SetLegendPosition(0, 0, 0, 0);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(0, 200);
    // canvas->SetRangeRatio(0.7, 1.3);
    canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    TString beamInfo = TString::Format("e+ beam (%.0lf GeV)", energy);
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, beamInfo);

    TString runInfo = TString::Format("%s channel, Run %d (EM scan @ %s, %.0lf GeV)", fiberType.Data(), run, centerTowerTag_.Data(), energy);
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    if( noFit_ ) {
      TString histInfo = TString::Format("Hist. statistics (# events = %.0lf):", h_eDep->Integral(0, h_eDep->GetNbinsX()+1));
      canvas->RegisterLatex(0.16, 0.87, 62, 0.6, histInfo);
      TString muInfo    = TString::Format("mean = %.2lf #pm %.2lf GeV", mean, absUnc_mean);
      TString sigmaInfo = TString::Format("std.dev. = %.2lf #pm %.2lf GeV", stdDev, absUnc_stdDev);
      TString resolInfo = TString::Format("std.dev/mean = %.2lf #pm %.2lf", resol, absUnc_resol);
      canvas->RegisterLatex(0.16, 0.83, 42, 0.6, muInfo);
      canvas->RegisterLatex(0.16, 0.79, 42, 0.6, sigmaInfo);
      canvas->RegisterLatex(0.16, 0.75, 42, 0.6, resolInfo);
    }
    else {
      TString fitInfo = TString::Format("Fit results (#chi2/nDOF = %.2lf/%.0lf):", fitter.Get("chi2"), fitter.Get("nDOF"));
      canvas->RegisterLatex(0.16, 0.87, 62, 0.6, fitInfo);

      TString muInfo    = TString::Format("#mu = %.2lf #pm %.2lf GeV", fitter.Get("mu"), fitter.GetUnc("mu"));
      TString sigmaInfo = TString::Format("#sigma = %.2lf #pm %.2lf GeV", fitter.Get("sigma"), fitter.GetUnc("sigma"));
      TString resolInfo = TString::Format("#sigma/#mu = %.2lf #pm %.2lf", fitter.Get("resol"), fitter.GetUnc("resol"));
      canvas->RegisterLatex(0.16, 0.83, 42, 0.6, muInfo);
      canvas->RegisterLatex(0.16, 0.79, 42, 0.6, sigmaInfo);
      canvas->RegisterLatex(0.16, 0.75, 42, 0.6, resolInfo);
    }

    if( use_partialTower_ ) {
      if( tag_partialTower_.Contains("near") ) {
        TString towerName = tag_partialTower_;
        towerName.ReplaceAll("near", "");
        TString sumInfo = TString::Format("Sum of the towers near %s only (9 towers)", towerName.Data());
        canvas->RegisterLatex(0.16, 0.71, 42, 0.5, sumInfo);
      }
    }

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);
    canvas->Draw("L");

    if( noFit_ )
      Fill_TGraph(fiberType, i_point, energy, mean, absUnc_mean, resol, absUnc_resol);
    else
      Fill_TGraph(fiberType, i_point, energy, fitter.Get("mu"), fitter.GetUnc("mu"), fitter.Get("resol"), fitter.GetUnc("resol"));
  }

  void Fill_TGraph(TString fiberType, int i_point, double energy, 
                   double mu, double absUnc_mu, double resol, double absUnc_resol) {

    map_resol_[fiberType]->SetPoint(i_point, energy, resol);
    map_resol_[fiberType]->SetPointError(i_point, 0, 0, absUnc_resol, absUnc_resol);

    double linearity     = mu / energy;
    double unc_linearity = absUnc_mu / energy;
    if( fiberType == "Sum" ) { // -- divide one more
      linearity /= 2.0;
      unc_linearity /= 2.0;
      printf("linearity = %lf\n", linearity);
    }
    map_linearity_[fiberType]->SetPoint(i_point, energy, linearity);
    map_linearity_[fiberType]->SetPointError(i_point, 0, 0, unc_linearity, unc_linearity);
  }

  TString Get_FileName(int run) { 
    return TString::Format("%s/Hist_Run_%d.root", inputPath_.Data(), run);
  }

  double AbsUnc_AoverB(double A, double unc_A, double B, double unc_B) {
    if( B == 0 ) return 0; // -- A/B is not defined

    double relUnc_A = (A == 0) ? 0.0 : unc_A/A;
    double relUnc_B = (B == 0) ? 0.0 : unc_B/B;
    double relUnc = std::sqrt(relUnc_A*relUnc_A + relUnc_B*relUnc_B);

    return (A/B)*relUnc;
  }
};