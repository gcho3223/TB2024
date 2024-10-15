#include "header/SimplePlotTools.h"
#include "header/RunInfo.h"

class Calibrator {
public:
  Calibrator(TString inputPath): inputPath_(inputPath) { }

  void Set_PlotPath(TString plotPath) { plotPath_ = plotPath; }

  void Produce() {
    energy_calib_ = 60.0;
    map_calibRun_ = TB2024::GetMap_CalibRun();
    ProduceHist_IntADC_PerTower();

    Calc_CalibConst();
    ProducePlot_CalibConst();
  }

  void Produce(TString plotPath) {
    Set_PlotPath(plotPath);
    Produce();
  }

private:
  TString inputPath_ = "";
  TString plotPath_ = "./";
  int nModule_ = 9;
  int nTower_ = 4;

  double energy_calib_;

  std::map<TString, int> map_calibRun_;
  std::map<TString, double> map_meanIntADC_; 
  std::map<TString, double> map_calibConst_;

  TString Get_FileName(int run) { 
    return TString::Format("%s/Hist_Run_%d.root", inputPath_.Data(), run);
  }

  void ProduceHist_IntADC_PerTower() {
    for(int i_mo=0; i_mo<nModule_; ++i_mo) {
      int moduleNum = i_mo+1;

      for(int i_tower=0; i_tower<nTower_; ++i_tower) {
        int towerNum = i_tower+1;

        ProduceHist_IntADC_PerTower(moduleNum, towerNum);
      } // -- iter. over tower
    } // -- iter. over module
  }

  void ProduceHist_IntADC_PerTower(int moduleNum, int towerNum) {
    TString towerTag = TString::Format("M%d-T%d", moduleNum, towerNum);
    int run = map_calibRun_[towerTag];
    TString fileName = Get_FileName(run);

    TString tag_c = towerTag+"-C";
    TString tag_s = towerTag+"-S";

    TString histName_c = "h_intADC_"+tag_c+"_DWCPSMC";
    TString histName_s = "h_intADC_"+tag_s+"_DWCPSMC";

    TH1D* h_c = PlotTool::Get_Hist(fileName, histName_c);
    TH1D* h_s = PlotTool::Get_Hist(fileName, histName_s);

    TString canvasName = TString::Format("intADC_%s_run%d", towerTag.Data(), run);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("intADC", "# events");

    TString legend_c = TString::Format("C: (mean, std. dev) = (%.0lf, %.0lf)", h_c->GetMean(), h_c->GetStdDev());
    TString legend_s = TString::Format("S: (mean, std. dev) = (%.0lf, %.0lf)", h_s->GetMean(), h_s->GetStdDev());

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

    TString runInfo = TString::Format("Run %d (calib. run for %s)", run, towerTag.Data());
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    double nEvent = h_c->Integral();
    TString nEventInfo = TString::Format("# events = %.0lf", nEvent);
    canvas->RegisterLatex(0.16, 0.87, 42, 0.6, nEventInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);
    canvas->Draw("HIST");

    // -- mean(intADC)
    map_meanIntADC_.insert( std::make_pair(tag_c, h_c->GetMean()) );
    map_meanIntADC_.insert( std::make_pair(tag_s, h_s->GetMean()) );
  }

  void Calc_CalibConst() {
    printf("Calculate calibration constant...\n");

    for(auto& pair : map_meanIntADC_ ) {
      TString tag = pair.first;
      double mean = pair.second;
      double calibConst = energy_calib_ / mean;

      // -- copy to preset.h
      printf("{\"%s\", %lf},\n", tag.Data(), calibConst);
      map_calibConst_.insert( std::make_pair(tag, calibConst) );
    }
  }

  void ProducePlot_CalibConst() {
    TH1D* h_const_c = MakeHist_CalibConst("C");
    TH1D* h_const_s = MakeHist_CalibConst("S");
    h_const_c->LabelsOption("v");
    h_const_s->LabelsOption("v");

    TString canvasName = TString::Format("calibConst_wrt%.0lfGeV", energy_calib_);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("DRC tower", "calib. const. (w.r.t. 60 GeV)");

    canvas->Register(h_const_c, "C channel", kBlue);
    canvas->Register(h_const_s, "S channel", kRed);

    canvas->SetLegendPosition(0.60, 0.82, 0.95, 0.95);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(0, 200);
    // canvas->SetRangeRatio(0.7, 1.3);
    canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    // TString runInfo = TString::Format("Run %d (calib. run for %s)", run, towerTag.Data());
    // canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    // double nEvent = h_c->Integral();
    // TString nEventInfo = TString::Format("# events = %.0lf", nEvent);
    // canvas->RegisterLatex(0.16, 0.87, 42, 0.6, nEventInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);
    canvas->Draw();
  }

  TH1D* MakeHist_CalibConst(TString fiberType) {
    int nBin = 36; // -- (9 modules * 4 towers)
    TH1D* h_calibConst = new TH1D("h_calibConst_"+fiberType, "", nBin, 0, nBin);

    int i_bin = 1;
    for(int i_mo=0; i_mo<nModule_; ++i_mo) {
      int moduleNum = i_mo+1;

      for(int i_tower=0; i_tower<nTower_; ++i_tower) {
        int towerNum = i_tower+1;
        TString binLabel = TString::Format("M%d-T%d", moduleNum, towerNum);
        TString fiberTag = binLabel + "-" + fiberType;
        double calibConst = map_calibConst_[fiberTag];

        h_calibConst->GetXaxis()->SetBinLabel(i_bin, binLabel);
        h_calibConst->SetBinContent(i_bin, calibConst);
        h_calibConst->SetBinError(i_bin, 0);

        i_bin++;
      } // -- iter. over tower
    } // -- iter. over module

    return h_calibConst;
  }
};