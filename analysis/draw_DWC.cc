#include "TBread.h"
#include "TButility.h"

#include <vector>
#include <iostream>
#include <filesystem>
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
    // int fMaxFile = std::stoi(argv[3]);
    // int fMaxEvent = -1;
    int fMaxFile  = -1;

    fs::path dir("./DWC");   
    if (!(fs::exists(dir))) fs::create_directory(dir);

    // Load mapping
    TButility util = TButility();
    util.LoadMapping("../mapping/mapping_TB2024_v1.root");

    // Get CIDs
    TBcid cid_DWC1_R = util.GetCID("DWC1R");
    TBcid cid_DWC1_L = util.GetCID("DWC1L");
    TBcid cid_DWC1_U = util.GetCID("DWC1U");
    TBcid cid_DWC1_D = util.GetCID("DWC1D");

    TBcid cid_DWC2_R = util.GetCID("DWC2R");
    TBcid cid_DWC2_L = util.GetCID("DWC2L");
    TBcid cid_DWC2_U = util.GetCID("DWC2U");
    TBcid cid_DWC2_D = util.GetCID("DWC2D");

    // Set Reader
    TChain* evtChain = loadNtuple(fRunNum);
    TBevt<TBwaveform>* anEvt = new TBevt<TBwaveform>(); // Will use waveform data
    evtChain->SetBranchAddress("TBevt", &anEvt);

    // Set Maximum event
    if (fMaxEvent == -1)
        fMaxEvent = evtChain->GetEntries();

    if (fMaxEvent > evtChain->GetEntries())
        fMaxEvent = evtChain->GetEntries();

    // Preparing 2D histograms for DWC 1 & 2 position, correlation plots
    TH2D* dwc1_pos = new TH2D("dwc1_pos", "dwc1_pos;mm;mm;events", 480, -120., 120., 480, -120., 120.);
    TH2D* dwc2_pos = new TH2D("dwc2_pos", "dwc2_pos;mm;mm;events", 480, -120., 120., 480, -120., 120.);
    TH2D* dwc_x_corr = new TH2D("dwc_x_corr", "dwc_x_corr;DWC1_X_mm;DWC2_X_mm;events", 480, -120., 120., 480, -120., 120.);
    TH2D* dwc_y_corr = new TH2D("dwc_y_corr", "dwc_y_corr;DWC1_Y_mm;DWC2_Y_mm;events", 480, -120., 120., 480, -120., 120.);

    // Start Evt Loop to draw DWC plots
    for (int iEvt = 0; iEvt < fMaxEvent; iEvt++) {
        printProgress(iEvt, fMaxEvent);
        evtChain->GetEntry(iEvt); // Get event

        // Get each DWC1(2) R, L, U, D channels data using evt->data(TBcid cid);
        TBwaveform data_DWC1_R = anEvt->GetData(cid_DWC1_R);
        TBwaveform data_DWC1_L = anEvt->GetData(cid_DWC1_L);
        TBwaveform data_DWC1_U = anEvt->GetData(cid_DWC1_U);
        TBwaveform data_DWC1_D = anEvt->GetData(cid_DWC1_D);
        
        // Exercise 2 : Get DWC2 R, L, U, D channels data
        TBwaveform data_DWC2_R = anEvt->GetData(cid_DWC2_R) ; // Your answer here
        TBwaveform data_DWC2_L = anEvt->GetData(cid_DWC2_L) ; // Your answer here
        TBwaveform data_DWC2_U = anEvt->GetData(cid_DWC2_U) ; // Your answer here
        TBwaveform data_DWC2_D = anEvt->GetData(cid_DWC2_D) ; // Your answer here

        // Get each DWC1 R, L, U, D channels waveform using data.waveform();
        std::vector<short> waveform_DWC1_R = data_DWC1_R.waveform();
        std::vector<short> waveform_DWC1_L = data_DWC1_L.waveform();
        std::vector<short> waveform_DWC1_U = data_DWC1_U.waveform();
        std::vector<short> waveform_DWC1_D = data_DWC1_D.waveform();

        // Exercise 3 : Get DWC2 R, L, U, D channels waveform
        std::vector<short> waveform_DWC2_R = data_DWC2_R.waveform(); // Your answer here
        std::vector<short> waveform_DWC2_L = data_DWC2_L.waveform(); // Your answer here
        std::vector<short> waveform_DWC2_U = data_DWC2_U.waveform(); // Your answer here
        std::vector<short> waveform_DWC2_D = data_DWC2_D.waveform(); // Your answer here

        // Get DWC 1 R, L, U, D peak timing from their waveforms
        float time_DWC1_R = getLeadingEdgeTime(waveform_DWC1_R, 0.4, 1, 1000);
        float time_DWC1_L = getLeadingEdgeTime(waveform_DWC1_L, 0.4, 1, 1000);
        float time_DWC1_U = getLeadingEdgeTime(waveform_DWC1_U, 0.4, 1, 1000);
        float time_DWC1_D = getLeadingEdgeTime(waveform_DWC1_D, 0.4, 1, 1000);

        // Exercise 4 : Get DWC2 R, L, U, D peak timing from their waveforms
        float time_DWC2_R = getLeadingEdgeTime(waveform_DWC2_R, 0.4, 1, 1000); // Your answer here
        float time_DWC2_L = getLeadingEdgeTime(waveform_DWC2_L, 0.4, 1, 1000); // Your answer here
        float time_DWC2_U = getLeadingEdgeTime(waveform_DWC2_U, 0.4, 1, 1000); // Your answer here
        float time_DWC2_D = getLeadingEdgeTime(waveform_DWC2_D, 0.4, 1, 1000); // Your answer here

        // TB2024 20240814 result (2800V, leading edge 10%)
        // float dwc1_horizontal_Slope = -0.2162; // This is calib. const. for downstream -> upstream view
        // float dwc1_horizontal_Offset = -0.2047; // This is calib. const. for downstream -> upstream view
        // float dwc1_Vertical_Slope = -0.2021;    // This is calib. const. for downstream -> upstream view
        // float dwc1_Vertical_Offset = -0.6291;  // This is calib. const. for downstream -> upstream view

        // // TB2024 20240814 result (2800V, leading edge 10%)
        // float dwc1_horizontal_Slope  = 0.2162; // This is calib. const. for upstream -> downstream view
        // float dwc1_horizontal_Offset = 0.2047; // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Slope    = -0.202;    // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Offset   = -0.3099;  // This is calib. const. for upstream -> downstream view

        // TB2024 20240814 result (2800V, leading edge 20%)
        // float dwc1_horizontal_Slope  = 0.1917; // This is calib. const. for upstream -> downstream view
        // float dwc1_horizontal_Offset = -0.05722; // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Slope    = -0.1864;    // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Offset   = 0.02128;  // This is calib. const. for upstream -> downstream view

        // TB2024 20240814 result (2800V, leading edge 30%)
        // float dwc1_horizontal_Slope  = 0.1864; // This is calib. const. for upstream -> downstream view
        // float dwc1_horizontal_Offset = -0.05611; // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Slope    = -0.1825;    // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Offset   = 0.06416;  // This is calib. const. for upstream -> downstream view

        // TB2024 20240814 result (2800V, leading edge 40%)
        float dwc1_horizontal_Slope  = 0.1830; // This is calib. const. for upstream -> downstream view
        float dwc1_horizontal_Offset = -0.04539; // This is calib. const. for upstream -> downstream view
        float dwc1_Vertical_Slope    = -0.1798;    // This is calib. const. for upstream -> downstream view
        float dwc1_Vertical_Offset   = 0.06994;  // This is calib. const. for upstream -> downstream view

        // // TB2024 20240814 result (2800V, leading edge 50%)
        // float dwc1_horizontal_Slope  = 0.1804; // This is calib. const. for upstream -> downstream view
        // float dwc1_horizontal_Offset = -0.03418; // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Slope    = -0.1775;    // This is calib. const. for upstream -> downstream view
        // float dwc1_Vertical_Offset   = 0.07222;  // This is calib. const. for upstream -> downstream view

        float dwc1_x_position = ( (float) (time_DWC1_R - time_DWC1_L ) * dwc1_horizontal_Slope) + dwc1_horizontal_Offset;
        float dwc1_y_position = ( (float) (time_DWC1_U - time_DWC1_D ) * dwc1_Vertical_Slope)   + dwc1_Vertical_Offset;

        // float dwc2_horizontal_Slope = -0.2013; // This is calib. const. for downstream -> upstream view
        // float dwc2_horizontal_Offset = -0.497; // This is calib. const. for downstream -> upstream view
        // float dwc2_Vertical_Slope = -0.204;    // This is calib. const. for downstream -> upstream view
        // float dwc2_Vertical_Offset = -0.6179;  // This is calib. const. for downstream -> upstream view

        // // TB2024 20240814 result (2800V, leading edge 10%)
        // float dwc2_horizontal_Slope  = 0.2013; // This is calib. const. for upstream -> downstream view
        // float dwc2_horizontal_Offset = 0.4983; // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Slope    = -0.204;    // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Offset   = -0.6097;  // This is calib. const. for upstream -> downstream view

        // TB2024 20240814 result (2800V, leading edge 20%)
        // float dwc2_horizontal_Slope  = 0.1856; // This is calib. const. for upstream -> downstream view
        // float dwc2_horizontal_Offset = 0.08805; // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Slope    = -0.1892;    // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Offset   = -0.03170;  // This is calib. const. for upstream -> downstream view

        // TB2024 20240814 result (2800V, leading edge 30%)
        // float dwc2_horizontal_Slope  = 0.1846; // This is calib. const. for upstream -> downstream view
        // float dwc2_horizontal_Offset = 0.05256; // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Slope    = -0.1848;    // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Offset   = 0.01848;  // This is calib. const. for upstream -> downstream view

        // // TB2024 20240814 result (2800V, leading edge 40%)
        float dwc2_horizontal_Slope  = 0.1818; // This is calib. const. for upstream -> downstream view
        float dwc2_horizontal_Offset = 0.02975; // This is calib. const. for upstream -> downstream view
        float dwc2_Vertical_Slope    = -0.1818;    // This is calib. const. for upstream -> downstream view
        float dwc2_Vertical_Offset   = 0.02572;  // This is calib. const. for upstream -> downstream view

        // // TB2024 20240814 result (2800V, leading edge 50%)
        // float dwc2_horizontal_Slope  = 0.1795; // This is calib. const. for upstream -> downstream view
        // float dwc2_horizontal_Offset = 0.02735; // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Slope    = -0.1793;    // This is calib. const. for upstream -> downstream view
        // float dwc2_Vertical_Offset   = 0.02857;  // This is calib. const. for upstream -> downstream view

        float dwc2_x_position = ( (float) (time_DWC2_R - time_DWC2_L) * dwc2_horizontal_Slope) + dwc2_horizontal_Offset;
        float dwc2_y_position = ( (float) (time_DWC2_U - time_DWC2_D) * dwc2_Vertical_Slope)   + dwc2_Vertical_Offset;

        // std::cout << "dwc2_x_position : " << dwc2_x_position << std::endl;
        // std::cout << "dwc2_y_position : " << dwc2_y_position << std::endl;

        // Filling 2D histogram to plot DWC 1 and 2 positions
        dwc1_pos->Fill(dwc1_x_position, dwc1_y_position);
        dwc2_pos->Fill(dwc2_x_position, dwc2_y_position); 
        // Filling DWC 1 and 2 X positions to plot DWC 1 & 2 x-position correlation plot
        dwc_x_corr->Fill(dwc1_x_position, dwc2_x_position);
        dwc_y_corr->Fill(dwc1_y_position, dwc2_y_position);
    }

    // Saving the DWC position & correlation plots in root file in ./dwc directory.
    std::string outFile = "./DWC/DWC_Run_" + std::to_string(fRunNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    dwc1_pos->Write();
    dwc2_pos->Write();
    dwc_x_corr->Write();
    dwc_y_corr->Write();

    outputRoot->Close();
}
