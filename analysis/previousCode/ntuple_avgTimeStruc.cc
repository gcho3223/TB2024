#include "TBread.h"
#include "TButility.h"

#include <filesystem>
#include <iostream>
#include <chrono>
#include <numeric>
#include <vector>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TH2.h"

#include "function.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {

    int fRunNum = std::stoi(argv[1]);
    int fMaxEvent = std::stoi(argv[2]);

    fs::path dir("./Avg");   
    if (!(fs::exists(dir))) fs::create_directory(dir);

    // initialize the utility class
    TButility util = TButility();
    util.LoadMapping("../mapping/mapping_TB2024_v1.root");
    
    // prepare CIDs that we want to use (CID = Channel ID)
    // 3x3 module CIDs
    std::vector<TBcid> cid_M1_C; std::vector<TBcid> cid_M1_S;
    std::vector<TBcid> cid_M2_C; std::vector<TBcid> cid_M2_S;
    std::vector<TBcid> cid_M3_C; std::vector<TBcid> cid_M3_S;
    std::vector<TBcid> cid_M4_C; std::vector<TBcid> cid_M4_S;
    std::vector<TBcid> cid_M5_C; std::vector<TBcid> cid_M5_S;
    std::vector<TBcid> cid_M6_C; std::vector<TBcid> cid_M6_S;
    std::vector<TBcid> cid_M7_C; std::vector<TBcid> cid_M7_S;
    std::vector<TBcid> cid_M8_C; std::vector<TBcid> cid_M8_S;
    std::vector<TBcid> cid_M9_C; std::vector<TBcid> cid_M9_S;

    for(int tower = 1; tower <= 4; tower++) {
        cid_M1_C.emplace_back(util.GetCID("M1-T" + std::to_string(tower) + "-C")); 
        cid_M2_C.emplace_back(util.GetCID("M2-T" + std::to_string(tower) + "-C")); 
        cid_M3_C.emplace_back(util.GetCID("M3-T" + std::to_string(tower) + "-C")); 
        cid_M4_C.emplace_back(util.GetCID("M4-T" + std::to_string(tower) + "-C")); 
        cid_M5_C.emplace_back(util.GetCID("M5-T" + std::to_string(tower) + "-C")); 
        cid_M6_C.emplace_back(util.GetCID("M6-T" + std::to_string(tower) + "-C")); 
        cid_M7_C.emplace_back(util.GetCID("M7-T" + std::to_string(tower) + "-C")); 
        cid_M8_C.emplace_back(util.GetCID("M8-T" + std::to_string(tower) + "-C")); 
        cid_M9_C.emplace_back(util.GetCID("M9-T" + std::to_string(tower) + "-C")); 

        cid_M1_S.emplace_back(util.GetCID("M1-T" + std::to_string(tower) + "-S")); 
        cid_M2_S.emplace_back(util.GetCID("M2-T" + std::to_string(tower) + "-S")); 
        cid_M3_S.emplace_back(util.GetCID("M3-T" + std::to_string(tower) + "-S")); 
        cid_M4_S.emplace_back(util.GetCID("M4-T" + std::to_string(tower) + "-S")); 
        cid_M5_S.emplace_back(util.GetCID("M5-T" + std::to_string(tower) + "-S")); 
        cid_M6_S.emplace_back(util.GetCID("M6-T" + std::to_string(tower) + "-S")); 
        cid_M7_S.emplace_back(util.GetCID("M7-T" + std::to_string(tower) + "-S")); 
        cid_M8_S.emplace_back(util.GetCID("M8-T" + std::to_string(tower) + "-S")); 
        cid_M9_S.emplace_back(util.GetCID("M9-T" + std::to_string(tower) + "-S")); 
    }

    // Aux. detectors
    TBcid cid_CC1 = util.GetCID("CC1"); // Cherenkov counter 1
    TBcid cid_CC2 = util.GetCID("CC2"); // Cherenkov counter 2

    TBcid cid_PS = util.GetCID("PS"); // Preshower
    TBcid cid_MC = util.GetCID("MC"); // Muon counter

    TBcid cid_DWC1R = util.GetCID("DWC1R"); // DWC 1
    TBcid cid_DWC1L = util.GetCID("DWC1L"); // DWC 1
    TBcid cid_DWC1U = util.GetCID("DWC1U"); // DWC 1
    TBcid cid_DWC1D = util.GetCID("DWC1D"); // DWC 1

    TBcid cid_DWC2R = util.GetCID("DWC2R"); // DWC 2
    TBcid cid_DWC2L = util.GetCID("DWC2L"); // DWC 2
    TBcid cid_DWC2U = util.GetCID("DWC2U"); // DWC 2
    TBcid cid_DWC2D = util.GetCID("DWC2D"); // DWC 2

    TBcid cid_LC2  = util.GetCID("LC2");  // Leakage Counter
    TBcid cid_LC3  = util.GetCID("LC3");  // Leakage Counter
    TBcid cid_LC4  = util.GetCID("LC4");  // Leakage Counter
    TBcid cid_LC5  = util.GetCID("LC5");  // Leakage Counter
    TBcid cid_LC7  = util.GetCID("LC7");  // Leakage Counter
    TBcid cid_LC8  = util.GetCID("LC8");  // Leakage Counter
    TBcid cid_LC9  = util.GetCID("LC9");  // Leakage Counter
    TBcid cid_LC10 = util.GetCID("LC10");  // Leakage Counter
    TBcid cid_LC11 = util.GetCID("LC11");  // Leakage Counter
    TBcid cid_LC12 = util.GetCID("LC12"); // Leakage Counter
    TBcid cid_LC13 = util.GetCID("LC13"); // Leakage Counter
    TBcid cid_LC14 = util.GetCID("LC14"); // Leakage Counter
    TBcid cid_LC15 = util.GetCID("LC15"); // Leakage Counter
    TBcid cid_LC16 = util.GetCID("LC16"); // Leakage Counter
    TBcid cid_LC20 = util.GetCID("LC20"); // Leakage Counter


    // prepare the histograms wa want to draw
    TH1F* hist_M1_T1_C = new TH1F("M1_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M1_T2_C = new TH1F("M1_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M1_T3_C = new TH1F("M1_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M1_T4_C = new TH1F("M1_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M2_T1_C = new TH1F("M2_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M2_T2_C = new TH1F("M2_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M2_T3_C = new TH1F("M2_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M2_T4_C = new TH1F("M2_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M3_T1_C = new TH1F("M3_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M3_T2_C = new TH1F("M3_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M3_T3_C = new TH1F("M3_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M3_T4_C = new TH1F("M3_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M4_T1_C = new TH1F("M4_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M4_T2_C = new TH1F("M4_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M4_T3_C = new TH1F("M4_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M4_T4_C = new TH1F("M4_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M5_T1_C = new TH1F("M5_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M5_T2_C = new TH1F("M5_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M5_T3_C = new TH1F("M5_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M5_T4_C = new TH1F("M5_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M6_T1_C = new TH1F("M6_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M6_T2_C = new TH1F("M6_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M6_T3_C = new TH1F("M6_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M6_T4_C = new TH1F("M6_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M7_T1_C = new TH1F("M7_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M7_T2_C = new TH1F("M7_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M7_T3_C = new TH1F("M7_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M7_T4_C = new TH1F("M7_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M8_T1_C = new TH1F("M8_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M8_T2_C = new TH1F("M8_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M8_T3_C = new TH1F("M8_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M8_T4_C = new TH1F("M8_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M9_T1_C = new TH1F("M9_T1_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M9_T2_C = new TH1F("M9_T2_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M9_T3_C = new TH1F("M9_T3_C" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M9_T4_C = new TH1F("M9_T4_C" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M1_T1_S = new TH1F("M1_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M1_T2_S = new TH1F("M1_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M1_T3_S = new TH1F("M1_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M1_T4_S = new TH1F("M1_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M2_T1_S = new TH1F("M2_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M2_T2_S = new TH1F("M2_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M2_T3_S = new TH1F("M2_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M2_T4_S = new TH1F("M2_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M3_T1_S = new TH1F("M3_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M3_T2_S = new TH1F("M3_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M3_T3_S = new TH1F("M3_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M3_T4_S = new TH1F("M3_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M4_T1_S = new TH1F("M4_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M4_T2_S = new TH1F("M4_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M4_T3_S = new TH1F("M4_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M4_T4_S = new TH1F("M4_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M5_T1_S = new TH1F("M5_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M5_T2_S = new TH1F("M5_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M5_T3_S = new TH1F("M5_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M5_T4_S = new TH1F("M5_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M6_T1_S = new TH1F("M6_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M6_T2_S = new TH1F("M6_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M6_T3_S = new TH1F("M6_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M6_T4_S = new TH1F("M6_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M7_T1_S = new TH1F("M7_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M7_T2_S = new TH1F("M7_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M7_T3_S = new TH1F("M7_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M7_T4_S = new TH1F("M7_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M8_T1_S = new TH1F("M8_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M8_T2_S = new TH1F("M8_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M8_T3_S = new TH1F("M8_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M8_T4_S = new TH1F("M8_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_M9_T1_S = new TH1F("M9_T1_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M9_T2_S = new TH1F("M9_T2_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M9_T3_S = new TH1F("M9_T3_S" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_M9_T4_S = new TH1F("M9_T4_S" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_CC1 = new TH1F("CC1", ";intADC;Events", 1000, 0, 1000);
    TH1F* hist_CC2 = new TH1F("CC2", ";intADC;Events", 1000, 0, 1000);

    TH1F* hist_PS = new TH1F("PS" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_MC = new TH1F("MC" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_LC2  = new TH1F("LC2 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC3  = new TH1F("LC3 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC4  = new TH1F("LC4 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC5  = new TH1F("LC5 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC7  = new TH1F("LC7 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC8  = new TH1F("LC8 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC9  = new TH1F("LC9 " , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC10 = new TH1F("LC10" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC11 = new TH1F("LC11" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC12 = new TH1F("LC12" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC13 = new TH1F("LC13" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC14 = new TH1F("LC14" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC15 = new TH1F("LC15" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC16 = new TH1F("LC16" , ";intADC;nEvents", 1000, 0, 1000);
    TH1F* hist_LC20 = new TH1F("LC20" , ";intADC;nEvents", 1000, 0, 1000);

    TH1F* hist_DWC1R = new TH1F("DWC1R", ";bin;ADC", 1000, 0, 1000);
    TH1F* hist_DWC1L = new TH1F("DWC1L", ";bin;ADC", 1000, 0, 1000);
    TH1F* hist_DWC1U = new TH1F("DWC1U", ";bin;ADC", 1000, 0, 1000);
    TH1F* hist_DWC1D = new TH1F("DWC1D", ";bin;ADC", 1000, 0, 1000);

    TH1F* hist_DWC2R = new TH1F("DWC2R", ";bin;ADC", 1000, 0, 1000);
    TH1F* hist_DWC2L = new TH1F("DWC2L", ";bin;ADC", 1000, 0, 1000);
    TH1F* hist_DWC2U = new TH1F("DWC2U", ";bin;ADC", 1000, 0, 1000);
    TH1F* hist_DWC2D = new TH1F("DWC2D", ";bin;ADC", 1000, 0, 1000);

    TChain* evtChain = loadNtuple(fRunNum);
    TBevt<TBwaveform>* anEvt = new TBevt<TBwaveform>(); // Will use waveform data
    evtChain->SetBranchAddress("TBevt", &anEvt);

    // Set Maximum event
    if (fMaxEvent == -1)
        fMaxEvent = evtChain->GetEntries();

    if (fMaxEvent > evtChain->GetEntries())
        fMaxEvent = evtChain->GetEntries();

    // Evt Loop
    for (int iEvt = 0; iEvt < fMaxEvent; iEvt++) {
        printProgress(iEvt, fMaxEvent);
        evtChain->GetEntry(iEvt); // Get event

        std::vector< std::vector<short> > wave_M1_C; std::vector< std::vector<short> > wave_M1_S;
        std::vector< std::vector<short> > wave_M2_C; std::vector< std::vector<short> > wave_M2_S;
        std::vector< std::vector<short> > wave_M3_C; std::vector< std::vector<short> > wave_M3_S;
        std::vector< std::vector<short> > wave_M4_C; std::vector< std::vector<short> > wave_M4_S;
        std::vector< std::vector<short> > wave_M5_C; std::vector< std::vector<short> > wave_M5_S;
        std::vector< std::vector<short> > wave_M6_C; std::vector< std::vector<short> > wave_M6_S;
        std::vector< std::vector<short> > wave_M7_C; std::vector< std::vector<short> > wave_M7_S;
        std::vector< std::vector<short> > wave_M8_C; std::vector< std::vector<short> > wave_M8_S;
        std::vector< std::vector<short> > wave_M9_C; std::vector< std::vector<short> > wave_M9_S;
        for(int tower = 0; tower < 4; tower++) {
            wave_M1_C.emplace_back( anEvt->GetData(cid_M1_C.at(tower)).waveform() ); 
            wave_M2_C.emplace_back( anEvt->GetData(cid_M2_C.at(tower)).waveform() ); 
            wave_M3_C.emplace_back( anEvt->GetData(cid_M3_C.at(tower)).waveform() ); 
            wave_M4_C.emplace_back( anEvt->GetData(cid_M4_C.at(tower)).waveform() ); 
            wave_M5_C.emplace_back( anEvt->GetData(cid_M5_C.at(tower)).waveform() ); 
            wave_M6_C.emplace_back( anEvt->GetData(cid_M6_C.at(tower)).waveform() ); 
            wave_M7_C.emplace_back( anEvt->GetData(cid_M7_C.at(tower)).waveform() ); 
            wave_M8_C.emplace_back( anEvt->GetData(cid_M8_C.at(tower)).waveform() ); 
            wave_M9_C.emplace_back( anEvt->GetData(cid_M9_C.at(tower)).waveform() ); 

            wave_M1_S.emplace_back( anEvt->GetData(cid_M1_S.at(tower)).waveform() ); 
            wave_M2_S.emplace_back( anEvt->GetData(cid_M2_S.at(tower)).waveform() ); 
            wave_M3_S.emplace_back( anEvt->GetData(cid_M3_S.at(tower)).waveform() ); 
            wave_M4_S.emplace_back( anEvt->GetData(cid_M4_S.at(tower)).waveform() ); 
            wave_M5_S.emplace_back( anEvt->GetData(cid_M5_S.at(tower)).waveform() ); 
            wave_M6_S.emplace_back( anEvt->GetData(cid_M6_S.at(tower)).waveform() ); 
            wave_M7_S.emplace_back( anEvt->GetData(cid_M7_S.at(tower)).waveform() ); 
            wave_M8_S.emplace_back( anEvt->GetData(cid_M8_S.at(tower)).waveform() ); 
            wave_M9_S.emplace_back( anEvt->GetData(cid_M9_S.at(tower)).waveform() ); 
        } 

        std::vector<short> wave_CC1 = (anEvt->GetData(cid_CC1)).waveform();
        std::vector<short> wave_CC2 = (anEvt->GetData(cid_CC2)).waveform();

        std::vector<short> wave_PS = (anEvt->GetData(cid_PS)).waveform();
        std::vector<short> wave_MC = (anEvt->GetData(cid_MC)).waveform();

        // Get waveform for DWCs
        std::vector<short> wave_DWC1R = (anEvt->GetData(cid_DWC1R)).waveform();
        std::vector<short> wave_DWC1L = (anEvt->GetData(cid_DWC1L)).waveform();
        std::vector<short> wave_DWC1U = (anEvt->GetData(cid_DWC1U)).waveform();
        std::vector<short> wave_DWC1D = (anEvt->GetData(cid_DWC1D)).waveform();
        std::vector<short> wave_DWC2R = (anEvt->GetData(cid_DWC2R)).waveform();
        std::vector<short> wave_DWC2L = (anEvt->GetData(cid_DWC2L)).waveform();
        std::vector<short> wave_DWC2U = (anEvt->GetData(cid_DWC2U)).waveform();
        std::vector<short> wave_DWC2D = (anEvt->GetData(cid_DWC2D)).waveform();

        std::vector<short> wave_LC2  = (anEvt->GetData(cid_LC2 )).waveform();
        std::vector<short> wave_LC3  = (anEvt->GetData(cid_LC3 )).waveform();
        std::vector<short> wave_LC4  = (anEvt->GetData(cid_LC4 )).waveform();
        std::vector<short> wave_LC5  = (anEvt->GetData(cid_LC5 )).waveform();
        std::vector<short> wave_LC7  = (anEvt->GetData(cid_LC7 )).waveform();
        std::vector<short> wave_LC8  = (anEvt->GetData(cid_LC8 )).waveform();
        std::vector<short> wave_LC9  = (anEvt->GetData(cid_LC9 )).waveform();
        std::vector<short> wave_LC10 = (anEvt->GetData(cid_LC10)).waveform();
        std::vector<short> wave_LC11 = (anEvt->GetData(cid_LC11)).waveform();
        std::vector<short> wave_LC12 = (anEvt->GetData(cid_LC12)).waveform();
        std::vector<short> wave_LC13 = (anEvt->GetData(cid_LC13)).waveform();
        std::vector<short> wave_LC14 = (anEvt->GetData(cid_LC14)).waveform();
        std::vector<short> wave_LC15 = (anEvt->GetData(cid_LC15)).waveform();
        std::vector<short> wave_LC16 = (anEvt->GetData(cid_LC16)).waveform();
        std::vector<short> wave_LC20 = (anEvt->GetData(cid_LC20)).waveform();


        for (int bin = 1; bin < 1001; bin++) {      

            hist_M1_T1_C->Fill(bin, (float) (wave_M1_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M1_T2_C->Fill(bin, (float) (wave_M1_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M1_T3_C->Fill(bin, (float) (wave_M1_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M1_T4_C->Fill(bin, (float) (wave_M1_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M2_T1_C->Fill(bin, (float) (wave_M2_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M2_T2_C->Fill(bin, (float) (wave_M2_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M2_T3_C->Fill(bin, (float) (wave_M2_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M2_T4_C->Fill(bin, (float) (wave_M2_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M3_T1_C->Fill(bin, (float) (wave_M3_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M3_T2_C->Fill(bin, (float) (wave_M3_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M3_T3_C->Fill(bin, (float) (wave_M3_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M3_T4_C->Fill(bin, (float) (wave_M3_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M4_T1_C->Fill(bin, (float) (wave_M4_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M4_T2_C->Fill(bin, (float) (wave_M4_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M4_T3_C->Fill(bin, (float) (wave_M4_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M4_T4_C->Fill(bin, (float) (wave_M4_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M5_T1_C->Fill(bin, (float) (wave_M5_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M5_T2_C->Fill(bin, (float) (wave_M5_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M5_T3_C->Fill(bin, (float) (wave_M5_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M5_T4_C->Fill(bin, (float) (wave_M5_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M6_T1_C->Fill(bin, (float) (wave_M6_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M6_T2_C->Fill(bin, (float) (wave_M6_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M6_T3_C->Fill(bin, (float) (wave_M6_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M6_T4_C->Fill(bin, (float) (wave_M6_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M7_T1_C->Fill(bin, (float) (wave_M7_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M7_T2_C->Fill(bin, (float) (wave_M7_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M7_T3_C->Fill(bin, (float) (wave_M7_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M7_T4_C->Fill(bin, (float) (wave_M7_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M8_T1_C->Fill(bin, (float) (wave_M8_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M8_T2_C->Fill(bin, (float) (wave_M8_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M8_T3_C->Fill(bin, (float) (wave_M8_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M8_T4_C->Fill(bin, (float) (wave_M8_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M9_T1_C->Fill(bin, (float) (wave_M9_C.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M9_T2_C->Fill(bin, (float) (wave_M9_C.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M9_T3_C->Fill(bin, (float) (wave_M9_C.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M9_T4_C->Fill(bin, (float) (wave_M9_C.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M1_T1_S->Fill(bin, (float) (wave_M1_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M1_T2_S->Fill(bin, (float) (wave_M1_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M1_T3_S->Fill(bin, (float) (wave_M1_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M1_T4_S->Fill(bin, (float) (wave_M1_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M2_T1_S->Fill(bin, (float) (wave_M2_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M2_T2_S->Fill(bin, (float) (wave_M2_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M2_T3_S->Fill(bin, (float) (wave_M2_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M2_T4_S->Fill(bin, (float) (wave_M2_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M3_T1_S->Fill(bin, (float) (wave_M3_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M3_T2_S->Fill(bin, (float) (wave_M3_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M3_T3_S->Fill(bin, (float) (wave_M3_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M3_T4_S->Fill(bin, (float) (wave_M3_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M4_T1_S->Fill(bin, (float) (wave_M4_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M4_T2_S->Fill(bin, (float) (wave_M4_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M4_T3_S->Fill(bin, (float) (wave_M4_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M4_T4_S->Fill(bin, (float) (wave_M4_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M5_T1_S->Fill(bin, (float) (wave_M5_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M5_T2_S->Fill(bin, (float) (wave_M5_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M5_T3_S->Fill(bin, (float) (wave_M5_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M5_T4_S->Fill(bin, (float) (wave_M5_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M6_T1_S->Fill(bin, (float) (wave_M6_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M6_T2_S->Fill(bin, (float) (wave_M6_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M6_T3_S->Fill(bin, (float) (wave_M6_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M6_T4_S->Fill(bin, (float) (wave_M6_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M7_T1_S->Fill(bin, (float) (wave_M7_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M7_T2_S->Fill(bin, (float) (wave_M7_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M7_T3_S->Fill(bin, (float) (wave_M7_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M7_T4_S->Fill(bin, (float) (wave_M7_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M8_T1_S->Fill(bin, (float) (wave_M8_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M8_T2_S->Fill(bin, (float) (wave_M8_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M8_T3_S->Fill(bin, (float) (wave_M8_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M8_T4_S->Fill(bin, (float) (wave_M8_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_M9_T1_S->Fill(bin, (float) (wave_M9_S.at(0).at(bin)) / (float) (fMaxEvent) );
            hist_M9_T2_S->Fill(bin, (float) (wave_M9_S.at(1).at(bin)) / (float) (fMaxEvent) );
            hist_M9_T3_S->Fill(bin, (float) (wave_M9_S.at(2).at(bin)) / (float) (fMaxEvent) );
            hist_M9_T4_S->Fill(bin, (float) (wave_M9_S.at(3).at(bin)) / (float) (fMaxEvent) );

            hist_CC1->Fill(bin, (float) (wave_CC1.at(bin)) / (float) (fMaxEvent) );
            hist_CC2->Fill(bin, (float) (wave_CC2.at(bin)) / (float) (fMaxEvent) );

            hist_PS->Fill(bin, (float) (wave_PS.at(bin)) / (float) (fMaxEvent) );
            hist_MC->Fill(bin, (float) (wave_MC.at(bin)) / (float) (fMaxEvent) );

            hist_LC2 ->Fill(bin, (float) (wave_LC2 .at(bin)) / (float) (fMaxEvent) );
            hist_LC3 ->Fill(bin, (float) (wave_LC3 .at(bin)) / (float) (fMaxEvent) );
            hist_LC4 ->Fill(bin, (float) (wave_LC4 .at(bin)) / (float) (fMaxEvent) );
            hist_LC5 ->Fill(bin, (float) (wave_LC5 .at(bin)) / (float) (fMaxEvent) );
            hist_LC7 ->Fill(bin, (float) (wave_LC7 .at(bin)) / (float) (fMaxEvent) );
            hist_LC8 ->Fill(bin, (float) (wave_LC8 .at(bin)) / (float) (fMaxEvent) );
            hist_LC9 ->Fill(bin, (float) (wave_LC9 .at(bin)) / (float) (fMaxEvent) );
            hist_LC10->Fill(bin, (float) (wave_LC10.at(bin)) / (float) (fMaxEvent) );
            hist_LC11->Fill(bin, (float) (wave_LC11.at(bin)) / (float) (fMaxEvent) );
            hist_LC12->Fill(bin, (float) (wave_LC12.at(bin)) / (float) (fMaxEvent) );
            hist_LC13->Fill(bin, (float) (wave_LC13.at(bin)) / (float) (fMaxEvent) );
            hist_LC14->Fill(bin, (float) (wave_LC14.at(bin)) / (float) (fMaxEvent) );
            hist_LC15->Fill(bin, (float) (wave_LC15.at(bin)) / (float) (fMaxEvent) );
            hist_LC16->Fill(bin, (float) (wave_LC16.at(bin)) / (float) (fMaxEvent) );
            hist_LC20->Fill(bin, (float) (wave_LC20.at(bin)) / (float) (fMaxEvent) );

            hist_DWC1R->Fill(bin, (float) (wave_DWC1R.at(bin)) / (float) (fMaxEvent) );
            hist_DWC1L->Fill(bin, (float) (wave_DWC1L.at(bin)) / (float) (fMaxEvent) );
            hist_DWC1U->Fill(bin, (float) (wave_DWC1U.at(bin)) / (float) (fMaxEvent) );
            hist_DWC1D->Fill(bin, (float) (wave_DWC1D.at(bin)) / (float) (fMaxEvent) );

            hist_DWC2R->Fill(bin, (float) (wave_DWC2R.at(bin)) / (float) (fMaxEvent) );
            hist_DWC2L->Fill(bin, (float) (wave_DWC2L.at(bin)) / (float) (fMaxEvent) );
            hist_DWC2U->Fill(bin, (float) (wave_DWC2U.at(bin)) / (float) (fMaxEvent) );
            hist_DWC2D->Fill(bin, (float) (wave_DWC2D.at(bin)) / (float) (fMaxEvent) );
        }
    }

    std::string outFile = "./Avg/Avg_Run_" + std::to_string(fRunNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    hist_M1_T1_C->Write();
    hist_M1_T2_C->Write();
    hist_M1_T3_C->Write();
    hist_M1_T4_C->Write();

    hist_M2_T1_C->Write();
    hist_M2_T2_C->Write();
    hist_M2_T3_C->Write();
    hist_M2_T4_C->Write();

    hist_M3_T1_C->Write();
    hist_M3_T2_C->Write();
    hist_M3_T3_C->Write();
    hist_M3_T4_C->Write();

    hist_M4_T1_C->Write();
    hist_M4_T2_C->Write();
    hist_M4_T3_C->Write();
    hist_M4_T4_C->Write();

    hist_M5_T1_C->Write();
    hist_M5_T2_C->Write();
    hist_M5_T3_C->Write();
    hist_M5_T4_C->Write();

    hist_M6_T1_C->Write();
    hist_M6_T2_C->Write();
    hist_M6_T3_C->Write();
    hist_M6_T4_C->Write();

    hist_M7_T1_C->Write();
    hist_M7_T2_C->Write();
    hist_M7_T3_C->Write();
    hist_M7_T4_C->Write();

    hist_M8_T1_C->Write();
    hist_M8_T2_C->Write();
    hist_M8_T3_C->Write();
    hist_M8_T4_C->Write();

    hist_M9_T1_C->Write();
    hist_M9_T2_C->Write();
    hist_M9_T3_C->Write();
    hist_M9_T4_C->Write();

    hist_M1_T1_S->Write();
    hist_M1_T2_S->Write();
    hist_M1_T3_S->Write();
    hist_M1_T4_S->Write();

    hist_M2_T1_S->Write();
    hist_M2_T2_S->Write();
    hist_M2_T3_S->Write();
    hist_M2_T4_S->Write();

    hist_M3_T1_S->Write();
    hist_M3_T2_S->Write();
    hist_M3_T3_S->Write();
    hist_M3_T4_S->Write();

    hist_M4_T1_S->Write();
    hist_M4_T2_S->Write();
    hist_M4_T3_S->Write();
    hist_M4_T4_S->Write();

    hist_M5_T1_S->Write();
    hist_M5_T2_S->Write();
    hist_M5_T3_S->Write();
    hist_M5_T4_S->Write();

    hist_M6_T1_S->Write();
    hist_M6_T2_S->Write();
    hist_M6_T3_S->Write();
    hist_M6_T4_S->Write();

    hist_M7_T1_S->Write();
    hist_M7_T2_S->Write();
    hist_M7_T3_S->Write();
    hist_M7_T4_S->Write();

    hist_M8_T1_S->Write();
    hist_M8_T2_S->Write();
    hist_M8_T3_S->Write();
    hist_M8_T4_S->Write();

    hist_M9_T1_S->Write();
    hist_M9_T2_S->Write();
    hist_M9_T3_S->Write();
    hist_M9_T4_S->Write();
    
    hist_CC1->Write();
    hist_CC2->Write();

    hist_PS->Write();
    hist_MC->Write();

    hist_LC2 ->Write();
    hist_LC3 ->Write();
    hist_LC4 ->Write();
    hist_LC5 ->Write();
    hist_LC7 ->Write();
    hist_LC8 ->Write();
    hist_LC9 ->Write();
    hist_LC10->Write();
    hist_LC11->Write();
    hist_LC12->Write();
    hist_LC13->Write();
    hist_LC14->Write();
    hist_LC15->Write();
    hist_LC16->Write();
    hist_LC20->Write();

    hist_DWC1R->Write();
    hist_DWC1L->Write();
    hist_DWC1U->Write();
    hist_DWC1D->Write();

    hist_DWC2R->Write();
    hist_DWC2L->Write();
    hist_DWC2U->Write();
    hist_DWC2D->Write();

    outputRoot->Close();
}
