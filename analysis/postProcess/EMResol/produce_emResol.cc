#include "EMResolution.h"

void produce_emResol() {
  TString plotPath = "./plot";
  PlotTool::Make_Dir_IfNotExist(plotPath);

  EMResolution resolution("./data", "M8-T2");
  resolution.Produce(plotPath);
}