#include "header/HistContainer.h"
#include "header/commonTool.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  // -- initial value -- //
  int nTotModule = 9;
  /////////////////////////

  TB2024::Timer timer;
  timer.Start();

  int fRunNum = std::stoi(argv[1]);
  int fMaxEvent = std::stoi(argv[2]);

  // -- histograms
  HistContainer hist_noCut("noCut");
  HistContainer hist_DWC("DWC");
  HistContainer hist_DWCPS("DWCPS");
  HistContainer hist_DWCPSMC("DWCPSMC");

  fs::path dir("./Hist");
  if( !(fs::exists(dir)) ) fs::create_directory(dir);

  // initialize the utility class
  TButility util = TButility();
  util.LoadMapping("../mapping/mapping_TB2024_v1.root");

  // -- DWC info. (offset): used later
  TFile* f_DWC = TFile::Open((TString)("./DWC/DWC_Run_" + std::to_string(fRunNum) + ".root"), "READ");
  TH2D* h_pos_unCorr_DWC1   = f_DWC->Get<TH2D>("dwc1_pos");
  TH2D* h_pos_unCorr_DWC2   = f_DWC->Get<TH2D>("dwc2_pos");
  std::vector<float> vec_offset_DWC1 = getDWCoffset(h_pos_unCorr_DWC1);
  std::vector<float> vec_offset_DWC2 = getDWCoffset(h_pos_unCorr_DWC2);
  f_DWC->Close();

  // -- detectors
  DWCPair theDWCPair(util, "DWC1", "DWC2");
  theDWCPair.Get_DWC1().Set_Offset(vec_offset_DWC1);
  theDWCPair.Get_DWC2().Set_Offset(vec_offset_DWC2);
  AuxDetector thePS(util, "PS");
  AuxDetector theMC(util, "MC");
  DRC theDRC(util, nTotModule);

  TChain* evtChain = loadNtuple(fRunNum);
  TBevt<TBwaveform>* anEvt = new TBevt<TBwaveform>(); // Will use waveform data
  evtChain->SetBranchAddress("TBevt", &anEvt);

  // Set Maximum event
  if( fMaxEvent == -1 )
    fMaxEvent = evtChain->GetEntries();

  if( fMaxEvent > evtChain->GetEntries() )
    fMaxEvent = evtChain->GetEntries();

  for(int i_ev = 0; i_ev < fMaxEvent; i_ev++) {
    printProgress(i_ev, fMaxEvent);
    evtChain->GetEntry(i_ev); // Get event

    hist_noCut.Fill( anEvt, theDRC, theDWCPair, thePS, theMC );

    // -- event selection
    if( !theDWCPair.Pass(anEvt) ) continue;   
    hist_DWC.Fill( anEvt, theDRC, theDWCPair, thePS, theMC );

    if( !thePS.Pass(anEvt) ) continue;
    hist_DWCPS.Fill(anEvt, theDRC, theDWCPair, thePS, theMC);

    if( !theMC.Pass(anEvt) ) continue;
    hist_DWCPSMC.Fill(anEvt, theDRC, theDWCPair, thePS, theMC);

  } // -- end of event loop

  std::string outFile = "./Hist/Hist_Run_" + std::to_string(fRunNum) + ".root";
  TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
  outputRoot->cd();

  hist_noCut.Write();
  hist_DWC.Write();
  hist_DWCPS.Write();
  hist_DWCPSMC.Write();

  outputRoot->Close();

  timer.PrintRunTime();
}