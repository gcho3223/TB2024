#include "header/detector/DWC.h"
#include "header/detector/DRC.h"

#include "function.h"
#include "header/commonTool.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  // -- initial value -- //
  int nTotModule = 9;
  int nTower = 4;
  /////////////////////////
  TB2024::Timer timer;
  timer.Start();

  int fRunNum = std::stoi(argv[1]);
  int fMaxEvent = std::stoi(argv[2]);

  // -- just to keep # processed events
  TH1D* h_nEvent = new TH1D("h_nEvent", "", 1, 0, 1);

  fs::path dir("./Avg");
  if( !(fs::exists(dir)) ) fs::create_directory(dir);

  // initialize the utility class
  TButility util = TButility();
  util.LoadMapping("../mapping/mapping_TB2024_v1.root");

  // -- detectors
  std::vector<TString> vec_subDWCTag = {"U", "D", "R", "L"}; // -- will be used later
  DWC theDWC1(util, "DWC1");
  DWC theDWC2(util, "DWC2");
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

  int nProcEvent = 0;
  for(int i_ev = 0; i_ev < fMaxEvent; i_ev++) {
    printProgress(i_ev, fMaxEvent);
    evtChain->GetEntry(i_ev); // Get event
    nProcEvent++;

    for(int i_mo=0; i_mo<nTotModule; ++i_mo) {
      int moduleNum = i_mo+1;

      for(int i_tower=0; i_tower<nTower; ++i_tower) {
        int towerNum = i_tower+1;
        theDRC.Get_Module(moduleNum).Get_Tower(towerNum).Count_Wave(anEvt);
      } // -- end of tower loop
    } // -- end of module loop

    // -- aux. detectors
    for(auto& subDWCTag : vec_subDWCTag ) {
      theDWC1.Get_SubDWC(subDWCTag).Count_Wave(anEvt);
      theDWC2.Get_SubDWC(subDWCTag).Count_Wave(anEvt);
    }
    thePS.Count_Wave(anEvt);
    theMC.Count_Wave(anEvt);
  } // -- end of event loop

  std::string outFile = "./Avg/Avg_Run_" + std::to_string(fRunNum) + ".root";
  TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
  outputRoot->cd();
  // -- # event
  h_nEvent->SetBinContent(1, nProcEvent);
  h_nEvent->SetBinError(1, 0);
  h_nEvent->Write();

  // -- average time structure
  for(auto& subDWCTag : vec_subDWCTag ) {
    theDWC1.Get_SubDWC(subDWCTag).GetHist_ATS()->Write();
    theDWC2.Get_SubDWC(subDWCTag).GetHist_ATS()->Write();
  }
  thePS.GetHist_ATS()->Write();
  theMC.GetHist_ATS()->Write();
  for(int i_mo=0; i_mo<nTotModule; ++i_mo) {
    int moduleNum = i_mo+1;

    for(int i_tower=0; i_tower<nTower; ++i_tower) {
      int towerNum = i_tower+1;
      theDRC.Get_Module(moduleNum).Get_Tower(towerNum).Get_Fiber("c").GetHist_ATS()->Write();
      theDRC.Get_Module(moduleNum).Get_Tower(towerNum).Get_Fiber("s").GetHist_ATS()->Write();
    } // -- end of tower loop
  } // -- end of module loop
  outputRoot->Close();

  timer.PrintRunTime();
}