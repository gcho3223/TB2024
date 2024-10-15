#include "header/SimplePlotTools.h"
#include "header/RunInfo.h"
#include "header/GausFitter.h"

class ScaleFactor {
public:
  ScaleFactor(TString inputPath, TString refTowerTag):
  inputPath_(inputPath), refTowerTag_(refTowerTag) {

  }

  void Set_PlotPath(TString plotPath) { plotPath_ = plotPath; }

  void Produce() {
    double energy_ref = 59.52; // -- 99.2% deposit in 3x3 modules

    map_calibRun_ = TB2024::GetMap_CalibRun();
    theRun_ = map_calibRun_[refTowerTag_];

    ProducePlot_EDep_PerTower();

    ProducePlot_EDepAll("C");
    ProducePlot_EDepAll("S");

    Calc_SF(energy_ref);
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

  std::map<TString, int> map_calibRun_;
  int theRun_;

  // -- mu: mean from the fit
  std::map<TString, double> map_mu_;
  std::map<TString, double> map_sf_;

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

    TH1D* h_eDepAll = PlotTool::Get_Hist(fileName, histName);

    GausFitter fitter(h_eDepAll);
    fitter.Fit();

    printf("[Fit results] (mu, sigma) = (%lf, %lf) --> rel. resolution = %.3lf\n", 
      fitter.Get("mu"), fitter.Get("sigma"), fitter.Get("resol"));

    // -- canvas
    TString canvasName = TString::Format("eDepAll_noSF-%s_run%d", fiberType.Data(), theRun_);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Energy deposit [GeV]", "# events");

    int color = (fiberType == "C") ? kBlue : kRed;
    canvas->Register(h_eDepAll, "", color);

    canvas->SetLegendPosition(0, 0, 0, 0);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(0, 200);
    // canvas->SetRangeRatio(0.7, 1.3);
    canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("%s channel, Run %d (calib. run for %s)", fiberType.Data(), theRun_, refTowerTag_.Data());
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    TString fitInfo = TString::Format("Fit results (#chi2/nDOF = %.2lf/%.0lf):", fitter.Get("chi2"), fitter.Get("nDOF"));
    canvas->RegisterLatex(0.16, 0.87, 62, 0.6, fitInfo);
    TString muInfo    = TString::Format("#mu = %.2lf #pm %.2lf GeV", fitter.Get("mu"),    fitter.GetUnc("mu"));
    TString sigmaInfo = TString::Format("#sigma = %.2lf #pm %.2lf GeV", fitter.Get("sigma"), fitter.GetUnc("sigma"));
    TString resolInfo = TString::Format("#mu/#sigma = %.2lf #pm %.2lf", fitter.Get("resol"), fitter.GetUnc("resol"));

    canvas->RegisterLatex(0.16, 0.83, 42, 0.6, muInfo);
    canvas->RegisterLatex(0.16, 0.79, 42, 0.6, sigmaInfo);
    canvas->RegisterLatex(0.16, 0.75, 42, 0.6, resolInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_); // -- path to be saved (default: "./")
    canvas->Draw("L");

    map_mu_.insert( std::make_pair(fiberType, fitter.Get("mu")) );
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

};