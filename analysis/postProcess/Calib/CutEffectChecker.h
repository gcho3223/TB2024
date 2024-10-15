#include "header/SimplePlotTools.h"

class CutEffectChecker {
public:
  CutEffectChecker(TString inputPath): inputPath_(inputPath) { }

  void Set_PlotPath(TString plotPath) { plotPath_ = plotPath; }

  void Produce() {
    // -- DWC
    ProudcePlot2D_DWCPosition("DWC1", "noCut");
    ProudcePlot2D_DWCPosition("DWC1", "DWC");
    ProudcePlot2D_DWCPosition("DWC2", "noCut");
    ProudcePlot2D_DWCPosition("DWC2", "DWC");
    // -- more plots
    // h2D_posCorrel_x_DWCPSMC (2D)
    // h_posDiffDWC_x_DWCPSMC (1D) 

    ProducePlot_PeakADC_noCut("PS");
    ProducePlot_PeakADC_noCut("MC");
    Comp_BeforeAfterCut("PS", "DWC", "DWCPS");
    Comp_BeforeAfterCut("MC", "DWCPS", "DWCPSMC");

    CompIntADC_EachCut("S");
    CompIntADC_EachCut("C");
  }

  void Produce(TString plotPath) {
    Set_PlotPath(plotPath);
    Produce();
  }

private:
  TString inputPath_ = "";
  TString plotPath_ = "./";
  int run_M8T2_ = 10477;

  void ProducePlot_PeakADC_noCut(TString detector) {
    int nRebin = 4;

    TString fileName = Get_FileName(run_M8T2_);
    TString histName = "h_peakADC_"+detector+"_noCut";

    TH1D* h_peakADC = PlotTool::Get_Hist(fileName, histName);
    h_peakADC->Rebin(nRebin);

    bool isLogY = (detector == "MC") ? true : false;
    TString canvasName = TString::Format("peakADC_noCut_%s_run%d", detector.Data(), run_M8T2_);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, isLogY);
    TString titleY = TString::Format("# event / %d", nRebin);
    canvas->SetTitle("peakADC", titleY);

    TString legend = "undefined";
    if( detector == "PS" ) legend = "Preshower";
    if( detector == "MC" ) legend = "Muon counter";

    canvas->Register(h_peakADC, legend, kBlack);

    canvas->SetLegendPosition(0.50, 0.80, 0.95, 0.91);

    if( detector == "MC" ) canvas->SetRangeX(0, 500);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(2000, 4000);
    // canvas->SetRangeRatio(0.7, 1.3);
    canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("%s, Run %d (calib. run for M8T2)", detector.Data(), run_M8T2_);
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    // canvas->RegisterLatex(0.16, 0.87, 42, 0.6, CutInfo(detector));

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);

    canvas->Draw("HIST");
  }

  void CompIntADC_EachCut(TString fiberType) {
    TString fileName = Get_FileName(run_M8T2_);

    TString fiberTag = TString::Format("M8-T2-%s", fiberType.Data());
    TString histName_base = TString::Format("h_intADC_%s", fiberTag.Data());
    TString histName_noCut   = histName_base + "_noCut";
    TString histName_DWC     = histName_base + "_DWC";
    TString histName_DWCPS   = histName_base + "_DWCPS";
    TString histName_DWCPSMC = histName_base + "_DWCPSMC";

    TH1D* h_noCut   = PlotTool::Get_Hist(fileName, histName_noCut);
    TH1D* h_DWC     = PlotTool::Get_Hist(fileName, histName_DWC);
    TH1D* h_DWCPS   = PlotTool::Get_Hist(fileName, histName_DWCPS);
    TH1D* h_DWCPSMC = PlotTool::Get_Hist(fileName, histName_DWCPSMC);

    h_noCut->SetLineWidth(2);
    h_DWC->SetLineWidth(2);
    h_DWCPS->SetLineWidth(2);
    h_DWCPSMC->SetLineWidth(2);

    TString canvasName = TString::Format("compIntADC_eachCut_%s_run%d", fiberType.Data(), run_M8T2_);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    canvas->SetTitle("intADC", "# events");

    canvas->Register(h_noCut,   GetLegend("no cut", h_noCut), kBlack);
    canvas->Register(h_DWC,     GetLegend("+ DWC cut", h_DWC), kBlue);
    canvas->Register(h_DWCPS,   GetLegend("+ PS cut", h_DWCPS), kGreen+2);
    canvas->Register(h_DWCPSMC, GetLegend("+ MC cut", h_DWCPSMC), kViolet);

    canvas->SetLegendPosition(0.50, 0.72, 0.95, 0.91);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(2000, 4000);
    // canvas->SetRangeRatio(0.7, 1.3);
    // canvas->SetAutoRangeY();
    canvas->SetRangeY(0, 720);
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("%s, Run %d (calib. run for M8T2)", fiberTag.Data(), run_M8T2_);
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_); // -- path to be saved (default: "./")

    canvas->Draw("HIST");
  }

  TString GetLegend(TString legend_base, TH1D* h) {
    return TString::Format("%s (# evt. = %.0lf)", legend_base.Data(), h->Integral());
  }

  void Comp_BeforeAfterCut(TString detector, TString tag_before, TString tag_after) {
    int nRebin = 4;

    TString fileName = Get_FileName(run_M8T2_);
    TString histName_base = TString::Format("h_peakADC_%s", detector.Data());

    TString histName_before = histName_base+"_"+tag_before;
    TString histName_after  = histName_base+"_"+tag_after;

    TH1D* h_before = PlotTool::Get_Hist(fileName, histName_before);
    TH1D* h_after  = PlotTool::Get_Hist(fileName, histName_after);
    // h_before->SetLineWidth(2);
    // h_after->SetLineWidth(2);

    h_before->Rebin(nRebin);
    h_after->Rebin(nRebin);

    TString canvasName = TString::Format("comp_beforeAfterCut_%s_run%d", detector.Data(), run_M8T2_);
    PlotTool::HistCanvas* canvas = new PlotTool::HistCanvas(canvasName, 0, 0);
    TString titleY = TString::Format("# event / %d", nRebin);
    canvas->SetTitle("peakADC", titleY);

    canvas->Register(h_before, "Before applying the cut", kBlack); // -- first element: denominator of the ratio
    canvas->Register(h_after,  "After applying the cut", kBlue);

    canvas->SetLegendPosition(0.50, 0.70, 0.95, 0.83);

    if( detector == "MC" ) canvas->SetRangeX(0, 250);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(2000, 4000);
    // canvas->SetRangeRatio(0.7, 1.3);
    canvas->SetAutoRangeY();
    // canvas->SetAutoRangeRatio();
    
    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.73, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("%s, Run %d (calib. run for M8T2)", detector.Data(), run_M8T2_);
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    canvas->RegisterLatex(0.16, 0.87, 42, 0.6, CutInfo(detector));

    double nEvent_before = h_before->Integral();
    double nEvent_after  = h_after->Integral();
    double frac_rejected = 1 - (nEvent_after/nEvent_before);
    TString nEventInfo = TString::Format("# events: %.0lf #rightarrow %.0lf (%.0lf%% rejected)", nEvent_before, nEvent_after, frac_rejected*100);
    canvas->RegisterLatex(0.16, 0.83, 42, 0.6, nEventInfo);

    // canvas->RemoveRatioError(); // remove error in the ratio (useful when the error is meaningless)

    canvas->SetSavePath(plotPath_);

    canvas->Draw("HIST");
  }

  TString Get_FileName(int run) { 
    return TString::Format("%s/Hist_Run_%d.root", inputPath_.Data(), run);
  }

  TString CutInfo(TString detector) {
    TString info = "undefined";
    if( detector == "PS" ) info = "PeakADC(PS) > 700";
    if( detector == "MC" ) info = "PeakADC(MC) < 40";

    return info;
  }

  void ProudcePlot2D_DWCPosition(TString detector, TString tag) {
    TString fileName = Get_FileName(run_M8T2_);
    TString histName = TString::Format("h2D_pos_%s_%s", detector.Data(), tag.Data());
    TH2D* h2D = PlotTool::Get_Hist2D(fileName, histName);

    TString canvasName = TString::Format("DWCPosition_%s_%s_run%d", detector.Data(), tag.Data(), run_M8T2_);
    PlotTool::Hist2DCanvas* canvas = new PlotTool::Hist2DCanvas(canvasName, 0, 0, 0);
    canvas->SetTitle("x [mm]", "y [mm]");

    canvas->Register(h2D);

    // canvas->SetRangeX(minX, maxX);
    // canvas->SetRangeY(minY, maxY);
    canvas->SetRangeZ(0, 31);
    // canvas->SetAutoRangeZ();

    canvas->RegisterLatex(0.14, 0.96, 62, 0.8, "TB2024");
    canvas->RegisterLatex(0.65, 0.96, 62, 0.6, "e+ beam (60 GeV)");

    TString runInfo = TString::Format("%s, Run %d (calib. run for M8T2)", detector.Data(), run_M8T2_);
    canvas->RegisterLatex(0.16, 0.91, 42, 0.6, runInfo);

    TString nEventInfo = TString::Format("# events = %.0lf", h2D->Integral());
    canvas->RegisterLatex(0.16, 0.87, 42, 0.6, nEventInfo);

    canvas->SetSavePath(plotPath_);

    canvas->Draw();
  }

};