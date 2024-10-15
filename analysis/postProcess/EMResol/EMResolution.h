#include "header/SimplePlotTools.h"
#include "header/RunInfo.h"
#include "header/GausFitter.h"

class EMResolution {
public:
  EMResolution(TString inputPath, TString centerTowerTag): 
  inputPath_(inputPath), centerTowerTag_(centerTowerTag) { }

  void Set_PlotPath(TString path) { plotPath_ = path; }

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
    resolFunc_C->SetParameter(0, 0);
    resolFunc_C->SetParameter(1, 0.2);
    resolFunc_C->SetParameter(2, 0.05);
    // resolFunc_C->SetParLimits(1, 0, 1e10); // -- positive
    resolFunc_C->SetLineColor(kBlue);

    TF1* resolFunc_S = new TF1("resolFunc_S", "TMath::Sqrt( ([0]/x)*([0]/x) + ([1]/TMath::Sqrt(x))*([1]/TMath::Sqrt(x))+[2]*[2] )", 0, 120);
    resolFunc_S->SetParameter(0, 0);
    resolFunc_S->SetParameter(1, 0.2);
    resolFunc_S->SetParameter(2, 0.05);
    // resolFunc_S->SetParLimits(1, 0, 1e10); // -- positive
    resolFunc_S->SetLineColor(kRed);

    TF1* resolFunc_sum = new TF1("resolFunc_sum", "TMath::Sqrt( ([0]/x)*([0]/x) + ([1]/TMath::Sqrt(x))*([1]/TMath::Sqrt(x))+[2]*[2] )", 0, 120);
    resolFunc_sum->SetParameter(0, 0);
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

    canvas->SetLegendPosition(0.24, 0.65, 0.95, 0.91);

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

    TH1D* h_eDep = PlotTool::Get_Hist(fileName, histName);
    GausFitter fitter(h_eDep);
    if( fiberType == "Sum" ) fitter.SetColor(kBlue);
    fitter.Fit();

    TString canvasName = TString::Format("eDep_%s_energy%.0lf_run%d", fiberType.Data(), energy, run);
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

    TString fitInfo = TString::Format("Fit results (#chi2/nDOF = %.2lf/%.0lf):", fitter.Get("chi2"), fitter.Get("nDOF"));
    canvas->RegisterLatex(0.16, 0.87, 62, 0.6, fitInfo);
    TString muInfo    = TString::Format("#mu = %.2lf #pm %.2lf GeV", fitter.Get("mu"), fitter.GetUnc("mu"));
    TString sigmaInfo = TString::Format("#sigma = %.2lf #pm %.2lf GeV", fitter.Get("sigma"), fitter.GetUnc("sigma"));
    canvas->RegisterLatex(0.16, 0.83, 42, 0.6, muInfo);
    canvas->RegisterLatex(0.16, 0.79, 42, 0.6, sigmaInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);
    canvas->Draw("L");

    // -- directly insert to TGraph
    map_resol_[fiberType]->SetPoint(i_point, energy, fitter.Get("resol"));
    map_resol_[fiberType]->SetPointError(i_point, 0, 0, fitter.GetUnc("resol"), fitter.GetUnc("resol"));

    double linearity     = fitter.Get("mu") / energy;
    double unc_linearity = fitter.GetUnc("mu") / energy;
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
};