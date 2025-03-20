#include "../header/SimplePlotTools.h"
#include "../header/RunInfo.h"

class PlotProducer {
public:
  PlotProducer(TString inputPath):inputPath_(inputPath) { Init(); }

  void Produce() {

    for(int i=0; i<9; ++i) {
      int moduleNum = i+1;
      ProducePlot_CompATS_PerModule(moduleNum, "C");
      ProducePlot_CompATS_PerModule(moduleNum, "S");
    }

    for(int i=0; i<9; ++i) {
      int moduleNum = i+1;
      for(int j=0; j<4; ++j) {
        int towerNum = j+1;
        ProducePlot_CompATS_PerTower(moduleNum, towerNum);
      }
    }

    // -- ATS in each calibration run (to check consistency over runs)
    for(auto& pair : map_calibRun_ )
      ProducePlot_ATS_PS(pair.second, pair.first);

    // -- ATS overlaid for each muon beam run (to check consistency over runs)
    ProducePlot_compATS_MuBeam_MC();
  }

private:
  TString inputPath_ = "undefined";

  std::map<TString, int> map_calibRun_;

  void Init() {
    map_calibRun_ = TB2024::GetMap_CalibRun();
  }

  void ProducePlot_CompATS_PerTower(int moduleNum, int towerNum) {
    TH1D* h_C   = GetATSHist(moduleNum, 1, "C");
    TH1D* h_S   = GetATSHist(moduleNum, 2, "S");

    TString canvasName = TString::Format("compATS_perT_M%d-T%d", moduleNum, towerNum);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Time bin", "ADC");

    canvas->Register(h_C, "Cerenkov (C)", kBlue); // -- first element: denominator of the ratio
    canvas->Register(h_S, "Scintillation (S)", kRed);

    // canvas->SetLegendColumn(2);
    canvas->SetLegendPosition(0.50, 0.16, 0.95, 0.40);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(2000, 4000);
    // canvas->SetRangeRatio(0.7, 1.3);
    // canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString towerInfo = TString::Format("M%d-T%d", moduleNum, towerNum);
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, towerInfo); // arguments: x, y, font type, font size, text

    canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    // canvas->SetSavePath("./output"); // -- path to be saved (default: "./")
    TString path = "./plots/Modules";
    if(canvasName.Contains("M1")) {path = "./plots/Modules/M1";}
    else if(canvasName.Contains("M2")) {path = "./plots/Modules/M2";}
    else if(canvasName.Contains("M3")) {path = "./plots/Modules/M3";}
    else if(canvasName.Contains("M4")) {path = "./plots/Modules/M4";}
    else if(canvasName.Contains("M5")) {path = "./plots/Modules/M5";}
    else if(canvasName.Contains("M6")) {path = "./plots/Modules/M6";}
    else if(canvasName.Contains("M7")) {path = "./plots/Modules/M7";}
    else if(canvasName.Contains("M8")) {path = "./plots/Modules/M8";}
    else if(canvasName.Contains("M9")) {path = "./plots/Modules/M9";}
    PlotTool::Make_Dir_IfNotExist(path);
    canvas->SetSavePath(path);

    canvas->Draw("HIST L");
  }

  void ProducePlot_CompATS_PerModule(int moduleNum, TString fiberType) {
    TH1D* h_T1 = GetATSHist(moduleNum, 1, fiberType);
    TH1D* h_T2 = GetATSHist(moduleNum, 2, fiberType);
    TH1D* h_T3 = GetATSHist(moduleNum, 3, fiberType);
    TH1D* h_T4 = GetATSHist(moduleNum, 4, fiberType);

    TString canvasName = TString::Format("compATS_M%d-%s", moduleNum, fiberType.Data());
    PlotTool::HistCanvaswRatio* canvas = new PlotTool::HistCanvaswRatio(canvasName, 0, 0);
    canvas->SetTitle("Time bin", "ADC", "T2-4/T1");

    canvas->Register(h_T1, "T1", kBlack); // -- first element: denominator of the ratio
    canvas->Register(h_T2, "T2", kBlue);
    canvas->Register(h_T3, "T3", kGreen+2);
    canvas->Register(h_T4, "T4", kViolet);

    canvas->SetLegendColumn(2);
    canvas->SetLegendPosition(0.60, 0.32, 0.95, 0.50);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(2000, 4000);
    canvas->SetRangeRatio(0.7, 1.3);
    // canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString moduleInfo = TString::Format("Module %d, %s channel", moduleNum, fiberType.Data());
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, moduleInfo); // arguments: x, y, font type, font size, text

    canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    // canvas->SetSavePath("./output"); // -- path to be saved (default: "./")
    TString path = "./plots/Modules";
    if(canvasName.Contains("M1")) {path = "./plots/Modules/M1";}
    else if(canvasName.Contains("M2")) {path = "./plots/Modules/M2";}
    else if(canvasName.Contains("M3")) {path = "./plots/Modules/M3";}
    else if(canvasName.Contains("M4")) {path = "./plots/Modules/M4";}
    else if(canvasName.Contains("M5")) {path = "./plots/Modules/M5";}
    else if(canvasName.Contains("M6")) {path = "./plots/Modules/M6";}
    else if(canvasName.Contains("M7")) {path = "./plots/Modules/M7";}
    else if(canvasName.Contains("M8")) {path = "./plots/Modules/M8";}
    else if(canvasName.Contains("M9")) {path = "./plots/Modules/M9";}
    PlotTool::Make_Dir_IfNotExist(path);
    canvas->SetSavePath(path);

    canvas->Draw("HIST L");
  }

  TString Get_FileName(int run) { 
    return TString::Format("%s/Avg_Run_%d.root", inputPath_.Data(), run); 
  }

  TH1D* GetATSHist(int moduleNum, int towerNum, TString fiberType) {
    TString towerTag = TString::Format("M%d-T%d", moduleNum, towerNum);
    int run = map_calibRun_[towerTag];
    TString fileName = Get_FileName(run);

    TString fullTag = TString::Format("%s-%s", towerTag.Data(), fiberType.Data());
    TString histName = "h_ats_"+fullTag;

    TH1D* h_temp = PlotTool::Get_Hist(fileName, histName);
    h_temp->SetLineWidth(2);

    return h_temp;
  }

  void ProducePlot_ATS_PS(int run, TString runTag) {
    TString fileName = Get_FileName(run);
    TString histName = "h_ats_PS";
    TH1D* h_PS = PlotTool::Get_Hist(fileName, histName);
    h_PS->SetLineWidth(2);

    TString canvasName = TString::Format("ATS_PS_run%d", run);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Time bin", "ADC");

    canvas->Register(h_PS, "PS", kBlack);

    canvas->SetLegendPosition(0, 0, 0, 0);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(2000, 4000);
    // canvas->SetRangeRatio(0.7, 1.3);
    // canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("Run %d (calib. for %s)", run, runTag.Data());
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo); // arguments: x, y, font type, font size, text

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    // canvas->SetSavePath("./output"); // -- path to be saved (default: "./")
    TString path = "./plots/Runs";
    PlotTool::Make_Dir_IfNotExist(path);
    canvas->SetSavePath(path);

    canvas->Draw("HIST L");
  }

  void ProducePlot_compATS_MuBeam_MC() {
    vector<Int_t> vec_color = {kBlack, kGreen+2, kBlue, kViolet};

    TString canvasName = TString::Format("ATS_MC");
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("Time bin", "ADC");

    int i_hist = 0;
    for(auto& pair : TB2024::map_muBeamRun) {
      TString tag = pair.first;
      int run     = pair.second;

      TString fileName = Get_FileName(run);
      TString histName = "h_ats_MC";
      TH1D* h_MC = PlotTool::Get_Hist(fileName, histName);
      h_MC->SetLineWidth(2);

      TString legend = TString::Format("Run %d (LC calib. for %s)", run, tag.Data());
      int color = vec_color[i_hist];

      canvas->Register(h_MC, legend, color);

      i_hist++;
    }

    canvas->SetLegendPosition(0.40, 0.16, 0.95, 0.40);

    // canvas->SetRangeX(minX, maxX);
    canvas->SetRangeY(3400, 3700);
    // canvas->SetRangeRatio(0.7, 1.3);
    // canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.71, 0.96, 62, 0.6, "#mu+ beam (160 GeV)");

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    // canvas->SetSavePath("./output"); // -- path to be saved (default: "./")

    canvas->Draw("HIST L");
  }

};

void comp_ATS() {
  PlotProducer producer("../../Avg");
  producer.Produce();
}