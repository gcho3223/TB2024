#include "header/SimplePlotTools.h"
#include "header/RunInfo.h"
#include "header/GausFitter.h"

class ScaleFactor {
public:
  ScaleFactor(TString inputPath, TString refTowerTag):
  inputPath_(inputPath), refTowerTag_(refTowerTag) {

  }

  void Set_PlotPath(TString plotPath) { plotPath_ = plotPath; }

  // -- use histogram mean & std. dev. instead of fit results
  void NoFit(bool noFit = kTRUE) { noFit_ = noFit; }

  void Use_PartialTower(TString tag_partialTower, double energy_ref) {
    use_partialTower_ = kTRUE;
    tag_partialTower_ = tag_partialTower;
    if( (tag_partialTower_ == "nearM8T2" && refTowerTag_ != "M8-T2") || 
        (tag_partialTower_ == "nearM9T1" && refTowerTag_ != "M9-T1") ||
        (tag_partialTower_ == "nearM5T1" && refTowerTag_ != "M5-T1") ||
        (tag_partialTower_ == "nearM5T3" && refTowerTag_ != "M5-T3") ) {
      printf("[ScaleFactor::Use_PartialTower] tag for partial tower is %s, but reference tower is %s!\n", tag_partialTower_.Data(), refTowerTag_.Data());
      throw std::invalid_argument("tower inconsistency is found");
    }
    energy_ref_ = energy_ref;
  }

  void Produce() {
    map_calibRun_ = TB2024::GetMap_CalibRun();
    theRun_ = map_calibRun_[refTowerTag_];

    ProducePlot_EDep_PerTower();

    ProducePlot_EDepAll("C");
    ProducePlot_EDepAll("S");

    Calc_SF(energy_ref_);
  }

  void Produce(TString plotPath) {
    Set_PlotPath(plotPath);
    Produce();
  }

private:
  TString inputPath_;
  TString plotPath_ = "./";
  TString refTowerTag_;

  int nModule_ = 9;
  int nTower_ = 4;

  double energy_ref_ = 59.52; // -- 99.2% deposit in 3x3 modules

  std::map<TString, int> map_calibRun_;
  int theRun_;

  // -- mu: mean from the fit
  std::map<TString, double> map_mu_;
  std::map<TString, double> map_sf_;

  bool noFit_ = kFALSE; // -- default: do fit

  // -- when partial # towers are used for SF calculation, not full 3x3 modules
  bool use_partialTower_ = kFALSE;
  TString tag_partialTower_ = "undefined"; // -- tag for hist. name (e.g. "nearM8T2" if the hist. = h_eDep_noSF_nearM8T2_DWCPSMC)

  void ProducePlot_EDep_PerTower() {
    for(int i_mo=0; i_mo<nModule_; ++i_mo) {
      int moduleNum = i_mo+1;

      for(int i_tower=0; i_tower<nTower_; ++i_tower) {
        int towerNum = i_tower+1;

        ProducePlot_EDep_PerTower(moduleNum, towerNum);
      } // -- iter. over tower
    } // -- iter. over module
  }

  void ProducePlot_EDep_PerTower(int moduleNum, int towerNum) {
    TString towerTag = TString::Format("M%d-T%d", moduleNum, towerNum);
    int run = map_calibRun_[towerTag];
    TString fileName = Get_FileName(run);

    TString tag_c = towerTag+"-C";
    TString tag_s = towerTag+"-S";

    TString histName_c = "h_eDep_noSF_"+tag_c+"_DWCPSMC";
    TString histName_s = "h_eDep_noSF_"+tag_s+"_DWCPSMC";

    TH1D* h_c = PlotTool::Get_Hist(fileName, histName_c);
    TH1D* h_s = PlotTool::Get_Hist(fileName, histName_s);

    TString canvasName = TString::Format("eDep_noSF_%s_run%d", towerTag.Data(), run);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Energy deposit [GeV]", "# events");

    TString legend_c = TString::Format("C: (mean, std. dev) = (%.2lf, %.2lf)", h_c->GetMean(), h_c->GetStdDev());
    TString legend_s = TString::Format("S: (mean, std. dev) = (%.2lf, %.2lf)", h_s->GetMean(), h_s->GetStdDev());

    canvas->Register(h_c, legend_c, kBlue);
    canvas->Register(h_s, legend_s, kRed);

    canvas->SetLegendPosition(0.40, 0.72, 0.95, 0.87);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(0, 200);
    // canvas->SetRangeRatio(0.7, 1.3);
    // canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("Run %d (calib. run for %s), w/o SF", run, towerTag.Data());
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    double nEvent = h_c->Integral();
    TString nEventInfo = TString::Format("# events = %.0lf", nEvent);
    canvas->RegisterLatex(0.16, 0.87, 42, 0.6, nEventInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);
    canvas->Draw("HIST");
  }

  void ProducePlot_EDepAll(TString fiberType) {
    TString fileName = Get_FileName(theRun_);
    TString histName = TString::Format("h_eDep_noSF_all-%s_DWCPSMC", fiberType.Data());
    if( use_partialTower_ )
      histName.ReplaceAll("noSF_all", "noSF_"+tag_partialTower_);

    TH1D* h_eDepAll =  PlotTool::Get_Hist(fileName, histName);

    // -- from histogram values (no fit)
    double mean   = h_eDepAll->GetMean();
    double stdDev = h_eDepAll->GetStdDev();
    double resol = stdDev / mean;

    GausFitter fitter(h_eDepAll);

    if( !noFit_ ) {
      fitter.Fit();
      printf("[Fit results] (mu, sigma) = (%lf, %lf) --> rel. resolution = %.3lf\n", 
        fitter.Get("mu"), fitter.Get("sigma"), fitter.Get("resol"));
    }
    else {
      printf("[Histogram] (mean, std. dev) = (%lf, %lf) --> rel. resolution = %.3lf\n",
        mean, stdDev, resol);
    }

    // -- canvas
    TString canvasName = TString::Format("eDepAll_noSF-%s_run%d", fiberType.Data(), theRun_);
    if( use_partialTower_ )
      canvasName.ReplaceAll("noSF", "noSF_"+tag_partialTower_);

    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Energy deposit [GeV]", "# events");

    int color = (fiberType == "C") ? kBlue : kRed;
    canvas->Register(h_eDepAll, "", color);

    canvas->SetLegendPosition(0, 0, 0, 0);

    canvas->SetRangeX(-20, 150);
    // canvas->SetRangeY(0, 200);
    // canvas->SetRangeRatio(0.7, 1.3);
    canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("%s channel, Run %d (calib. run for %s)", fiberType.Data(), theRun_, refTowerTag_.Data());
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    if( noFit_ ) {
      TString histInfo = TString::Format("Hist. statistics (# events = %.0lf):", h_eDepAll->Integral(0, h_eDepAll->GetNbinsX()+1));
      canvas->RegisterLatex(0.16, 0.87, 62, 0.6, histInfo);
      double absUnc_mean   = h_eDepAll->GetMeanError();
      double absUnc_stdDev = h_eDepAll->GetStdDevError();
      double absUnc_resol  = AbsUnc_AoverB(stdDev, absUnc_stdDev, mean, absUnc_mean);

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
      TString muInfo    = TString::Format("#mu = %.2lf #pm %.2lf GeV", fitter.Get("mu"),    fitter.GetUnc("mu"));
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

    canvas->SetSavePath(plotPath_); // -- path to be saved (default: "./")
    canvas->Draw("L");

    if( noFit_ ) map_mu_.insert( std::make_pair(fiberType, mean) );
    else         map_mu_.insert( std::make_pair(fiberType, fitter.Get("mu")) );
  }

  void Calc_SF(double energy_ref) {
    printf("Calculate scale factor...\n");

    for(auto& pair : map_mu_ ) {
      TString fiberType = pair.first;
      fiberType.ToLower();
      double mu = pair.second;

      double sf = energy_ref / mu;

      // -- copy to preset.h
      printf("{\"%s\", %lf},\n", fiberType.Data(), sf);
    }
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