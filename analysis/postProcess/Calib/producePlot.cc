#include "CutEffectChecker.h"
#include "Calibrator.h"
#include "ScaleFactor.h"

void producePlot() {
  TString inputPath = "./data";
  TString plotPath = "./plot";
  PlotTool::Make_Dir_IfNotExist(plotPath);

  CutEffectChecker checker(inputPath);
  checker.Produce(plotPath);

  Calibrator calibrator(inputPath);
  calibrator.Produce(plotPath);

  ScaleFactor sf(inputPath, "M8-T2");
  // ScaleFactor sf(inputPath, "M5-T1");
  sf.Produce(plotPath);
}