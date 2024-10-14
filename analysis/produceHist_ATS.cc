#include "header/detector/DRC.h"

#include "function.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;


int main(int argc, char** argv) {
  // -- initial value -- //
  int nTotModule = 9;
  int nTower = 4;
  /////////////////////////

  int fRunNum = std::stoi(argv[1]);
  int fMaxEvent = std::stoi(argv[2]);

  fs::path dir("./Avg");
  if( !(fs::exists(dir)) ) fs::create_directory(dir);

  // initialize the utility class
  TButility util = TButility();
  util.LoadMapping("../mapping/mapping_TB2024_v1.root");

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

    for(int i_mo=0; i_mo<nTotModule; ++i_mo) {
      int moduleNum = i_mo+1;

      for(int i_tower=0; i_tower<nTower; ++i_tower) {
        int towerNum = i_tower+1;
        theDRC.Get_Module(moduleNum).Get_Tower(towerNum).Count_Wave();
      } // -- end of tower loop
    } // -- end of module loop
  } // -- end of event loop

  std::string outFile = "./Avg/Avg_Run_" + std::to_string(fRunNum) + ".root";
  TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
  outputRoot->cd();
  for(int i_mo=0; i_mo<nTotModule; ++i_mo) {
    int moduleNum = i_mo+1;

    for(int i_tower=0; i_tower<nTower; ++i_tower) {
      int towerNum = i_tower+1;
      theDRC.Get_Module(moduleNum).Get_Tower(towerNum).Get_Fiber("c").GetHist_ATS()->Write();
      theDRC.Get_Module(moduleNum).Get_Tower(towerNum).Get_Fiber("s").GetHist_ATS()->Write();
    } // -- end of tower loop
  } // -- end of module loop
  outputRoot->Close(); 
}