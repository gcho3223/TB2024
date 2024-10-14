#pragma once

#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <numeric>

#include "TROOT.h"
#include "TStyle.h"
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>

//////////////////////////////////////////////////////////////////////////////
// For loading ntuples
//////////////////////////////////////////////////////////////////////////////

std::vector<int> myColorPalette {
  1, // "kBlack",
  2, // "kRed",
  4, // "kBlue",
  417, // "kGreen",
  616, // "kMagenta",
  433, // "kAzure"
  807, // "kOrange"
  399, // "kYellow"
  429 // kCyan
};

TChain* loadNtuple(int runNum) {
    TChain* evtChain = new TChain("event");
    for (int fn = 0; fn < 50; fn++) {
        std::string fileName = "ntuple_Run_" + std::to_string(runNum) + "_Wave_" + std::to_string(fn) + ".root";
        std::string filePath = "/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2024_DRC_TB_ntuple/Run_"  + std::to_string(runNum) + "/Run_" + std::to_string(runNum) + "_Wave/"+ fileName;
        if ( !access(filePath.c_str(), F_OK) ){
            std::cout << fn << " Ntuple file added to TChain : " << filePath << std::endl;
            evtChain->Add(filePath.c_str());
        }
    }
    return evtChain;
}

float getPed(std::vector<short> waveform) {
  return std::accumulate( waveform.begin() + 1, waveform.begin() + 101, 0.) / 100.;
}

float getPedfromBack(std::vector<short> waveform) {
  return std::accumulate( waveform.end() - 24, waveform.end()  - 124, 0.) / 100.;
}

float getMin(std::vector<short> waveform) {
  return *(std::min_element(waveform.begin() + 1, waveform.end() - 23));
}

float getMinFrom(std::vector<short> waveform, int from, int end) {
  int minus = waveform.size() - end;
  return *(std::min_element(waveform.begin() + from, waveform.end() - minus));
}

int getMinIdx(std::vector<short> waveform) {
  return std::distance( waveform.begin(), std::min_element(waveform.begin() + 1, waveform.end() - 23) );
}

int getMinIdxFrom(std::vector<short> waveform, int from, int end) {
  int minus = waveform.size() - end;
  return std::distance( waveform.begin(), std::min_element(waveform.begin() + from, waveform.end() - minus) );
}

double linearInterpolation(double x1, double y1, double x2, double y2, double threshold) {
    return x1 + (threshold - y1) * (x2 - x1) / (y2 - y1);
}

float interpolate(std::vector<short> waveform, int thrs_bin, float thrs) {
  float x0 = (float) (thrs_bin - 1);
  float x1 = (float) thrs_bin;
  float y0 = (float) getPed(waveform) - waveform.at(thrs_bin-1);
  float y1 = (float) getPed(waveform) - waveform.at(thrs_bin);

  return (float)( x0 + (thrs - y0) * (x1 - x0) / (y1 - y0) );
}

std::vector<float> GetAvg(std::vector<short> waveform, int maxEntry)
{
  std::vector<float> scaled_waveform;
  for(int i = 0; i < waveform.size(); i++)
    scaled_waveform.push_back( ( (float) waveform.at(i) / (float) maxEntry) );
  return scaled_waveform;
}

float GetInt(std::vector<short> waveform, int startBin, int endBin)
{
  float ped = std::accumulate(waveform.begin() + 1, waveform.begin() + 101, 0.) / 100.;
  
  std::vector<float> pedCorrectedWave;
  for (int i = 0; i < waveform.size(); i++)
    pedCorrectedWave.push_back(ped - waveform.at(i));

  return (std::accumulate(pedCorrectedWave.begin() + startBin, pedCorrectedWave.begin() + endBin, 0.));
}

double GetIntADC(std::vector<short> waveform, int xInit, int xFin) {
  double ped = 0;
  for (int i = 1; i < 101; i++)
    ped += (double)waveform.at(i) / 100.;

  double intADC_ = 0;
  for (int i = xInit; i < xFin; i++)
    intADC_ += ped - (double)waveform.at(i);

  return intADC_;
}

float GetPeak(std::vector<short> waveform, int startBin, int endBin)
{
  float ped = std::accumulate(waveform.begin() + 1, waveform.begin() + 101, 0.) / 100.;
  
  std::vector<float> pedCorrectedWave;
  for (int i = 0; i < waveform.size(); i++)
    pedCorrectedWave.push_back(ped - (float)waveform.at(i));

  return (*std::max_element(pedCorrectedWave.begin() + startBin, pedCorrectedWave.begin() + endBin));
}

float GetIntWithPed(std::vector<short> waveform, int startBin, int endBin, float ped)
{  
  std::vector<float> pedCorrectedWave;
  for (int i = 0; i < waveform.size(); i++)
    pedCorrectedWave.push_back(ped - (float)waveform.at(i));

  return (std::accumulate(pedCorrectedWave.begin() + startBin, pedCorrectedWave.begin() + endBin, 0.));
}

float GetPeakWithPed(std::vector<short> waveform, int startBin, int endBin, float ped)
{  
  std::vector<float> pedCorrectedWave;
  for (int i = 0; i < waveform.size(); i++)
    pedCorrectedWave.push_back(ped - (float)waveform.at(i));

  return (*std::max_element(pedCorrectedWave.begin() + startBin, pedCorrectedWave.begin() + endBin));
}


//////////////////////////////////////////////////////////////////////////////
// For DWC position
//////////////////////////////////////////////////////////////////////////////

// Transfer waveform bin index to time (nanosecond)
float getTime(float bin) {
  return 800. * (bin / 1000.);
}

// Get peak bin index from raw waveform (peak == minimum value)
int getPeakBin(std::vector<short> waveform) {
    return ( std::min_element(waveform.begin()+1, waveform.end()-23) - waveform.begin() );
}

int getLeadingEdgeBin(std::vector<short> waveform, float threshold, int start, int end) {

    float ped = getPed(waveform);
    std::vector<float> pedCorrWaveform;
    for(int idx = 0; idx < waveform.size(); idx++){
        pedCorrWaveform.emplace_back(ped - (float)waveform.at(idx));
    }

    float max = *max_element(pedCorrWaveform.begin()+start, pedCorrWaveform.begin()+end);
    // float max = *max_element(pedCorrWaveform.begin()+1, pedCorrWaveform.end()-23);
    float thr = max * threshold;

    for (int idx = 1; idx < pedCorrWaveform.size()-23; idx++){
        if (pedCorrWaveform.at(idx) >= thr)
            return idx;
    }
    return -1;
}

float getLeadingEdgeTime(std::vector<short> waveform, float threshold, int start, int end) {
    
    int leadingEdgeBin = getLeadingEdgeBin(waveform, threshold, start, end);

    float thr = GetPeak(waveform, start, end) * threshold;

    // std::cout << "leadingEdgeBin : " << leadingEdgeBin << std::endl;

    if (leadingEdgeBin == 1)
      return getTime(leadingEdgeBin);

    float interpolated_bin = interpolate(waveform, leadingEdgeBin, thr);
    // std::cout << "interpolated_bin : " << interpolated_bin << std::endl;
    return getTime(interpolated_bin);
}

// For 200 ns time window
float getLeadingEdgeTime3(std::vector<short> waveform, float threshold, int start, int end) {
    
    int leadingEdgeBin = getLeadingEdgeBin(waveform, threshold, start, end);

    float thr = GetPeak(waveform, start, end) * threshold;

    // std::cout << "leadingEdgeBin : " << leadingEdgeBin << std::endl;

    if (leadingEdgeBin == 1)
      return getTime(leadingEdgeBin);

    float interpolated_bin = interpolate(waveform, leadingEdgeBin, thr);
    // std::cout << "interpolated_bin : " << interpolated_bin << std::endl;

    return 200. * (interpolated_bin / 1000.);
}

// W/O interpolation
float getLeadingEdgeTime2(std::vector<short> waveform, float threshold, int start, int end) {
  int bin = getLeadingEdgeBin(waveform, threshold, start, end);

  // std::cout << "bin : " << bin << std::endl;
  return getTime(bin);
}

// Get peak timing from raw waveform (peak == minimum value)
float getPeakTime(std::vector<short> waveform) {
    int peakBin = getPeakBin(waveform);
    return (getTime(peakBin));
}

// Calculate DWC position using DWC waveform peak timing (timing == nanosecond)
// DWC X-axis position : { (Waveform peak timing from DWC Right ch) - (Waveform peak timing from DWC Left ch) } * (calibrated DWC x-axis slope value) + (calibrated DWC x-axis intercept value)
// DWC Y-axis position : { (Waveform peak timing from DWC Up ch) - (Waveform peak timing from DWC Down ch) } * (calibrated DWC y-axis slope value) + (calibrated DWC y-axis intercept value)
// Subtract x and y offset from calculated DWC x-axis and y-axis position to make mean value of DWC position plot aligns to center. That is, (0 mm, 0 mm) position.
// x and y offset can be obtained from non-corrected DWC position plot's mean value.
// std::vector<float> getDWC1position(std::vector<float> dwc1Time, float xOffset = 0.f, float yOffset = 0.f) {
std::vector<float> getDWC1position(std::vector<float> dwc1Time, std::vector<float> dwc1Offset) {
  // TB2024 20240814 result (2800V, leading edge 40%)
  float dwc1_horizontal_Slope  = 0.1830; // This is calib. const. for upstream -> downstream view
  float dwc1_horizontal_Offset = -0.04539; // This is calib. const. for upstream -> downstream view
  float dwc1_Vertical_Slope    = -0.1798;    // This is calib. const. for upstream -> downstream view
  float dwc1_Vertical_Offset   = 0.06994;  // This is calib. const. for upstream -> downstream view

    std::vector<float> dwc1Position;

    // dwc1Time should be {DWC 1 R time, DWC 1 L time, DWC 1 U time, DWC 1 D time}
    float horizontalPos =  ( (float)(dwc1Time.at(0) - dwc1Time.at(1)) * dwc1_horizontal_Slope ) + dwc1_horizontal_Offset - dwc1Offset.at(0);
    float verticalPos = ( (float)(dwc1Time.at(2) - dwc1Time.at(3)) * dwc1_Vertical_Slope ) + dwc1_Vertical_Offset - dwc1Offset.at(1);

    dwc1Position.push_back(horizontalPos);
    dwc1Position.push_back(verticalPos);

    return dwc1Position;
}

std::vector<float> getDWC2position(std::vector<float> dwc2Time, std::vector<float> dwc2Offset) {
    // // TB2024 20240814 result (2800V, leading edge 40%)
    float dwc2_horizontal_Slope  = 0.1818; // This is calib. const. for upstream -> downstream view
    float dwc2_horizontal_Offset = 0.02975; // This is calib. const. for upstream -> downstream view
    float dwc2_Vertical_Slope    = -0.1818;    // This is calib. const. for upstream -> downstream view
    float dwc2_Vertical_Offset   = 0.02572;  // This is calib. const. for upstream -> downstream view

    std::vector<float> dwc2Position;

    float horizontalPos = ( (float)(dwc2Time.at(0) - dwc2Time.at(1)) * dwc2_horizontal_Slope ) + dwc2_horizontal_Offset - dwc2Offset.at(0);
    float verticalPos = ( (float)(dwc2Time.at(2) - dwc2Time.at(3)) * dwc2_Vertical_Slope ) + dwc2_Vertical_Offset - dwc2Offset.at(1);

    dwc2Position.push_back(horizontalPos);
    dwc2Position.push_back(verticalPos);

    return dwc2Position;
}

// Calculate DWC position using DWC waveform peak timing (timing == clock value)
// To translate clock value to nanosecond : (clock * 25. / 1000.) == (nanosecond)
// Clock values can be obtained from fast mode event's evt.timing() function
// Other logics are same as above
std::vector<float> getDWC1positionUsingClock(std::vector<float> dwc1Time) {
    static float dwc1_horizontal_Slope  =  0.2162; 
    static float dwc1_horizontal_Offset =  0.2047; 
    static float dwc1_Vertical_Slope    =  -0.202; 
    static float dwc1_Vertical_Offset   =  -0.3099;

    std::vector<float> dwc1Position;

    float horizontalPos = -( ( (float)(dwc1Time.at(0) - dwc1Time.at(1)) * 25. / 1000. * dwc1_horizontal_Slope ) + dwc1_horizontal_Offset );
    float verticalPos = ( (float)(dwc1Time.at(2) - dwc1Time.at(3)) * 25. / 1000. * dwc1_Vertical_Slope ) + dwc1_Vertical_Offset;

    dwc1Position.push_back(horizontalPos);
    dwc1Position.push_back(verticalPos);

    return dwc1Position;
}

std::vector<float> getDWC2positionUsingClock(std::vector<float> dwc2Time) {
    static float dwc2_horizontal_Slope  = 0.2013; 
    static float dwc2_horizontal_Offset = 0.4983; 
    static float dwc2_Vertical_Slope    = -0.204; 
    static float dwc2_Vertical_Offset   = -0.6097;

    std::vector<float> dwc2Position;

    float horizontalPos = -( ( (float)(dwc2Time.at(0) - dwc2Time.at(1)) * 25. / 1000. * dwc2_horizontal_Slope ) + dwc2_horizontal_Offset );
    float verticalPos = ( (float)(dwc2Time.at(2) - dwc2Time.at(3)) * 25. / 1000. * dwc2_Vertical_Slope ) + dwc2_Vertical_Offset;

    dwc2Position.push_back(horizontalPos);
    dwc2Position.push_back(verticalPos);

    return dwc2Position;
}

// From non-corrected DWC 2D histogram, get its x and y position mean value and return them
std::vector<float> getDWCoffset(TH2D* dwcHist) {
    float xOffset = dwcHist->GetMean(1);
    float yOffset = dwcHist->GetMean(2);

    std::vector<float> dwcOffset;
    dwcOffset.push_back(xOffset);
    dwcOffset.push_back(yOffset);

    return dwcOffset;
}

//////////////////////////////////////////////////////////////////////////////
// For PID
//////////////////////////////////////////////////////////////////////////////

// Give DWC1, 2 correlation constraint, threshold set to 1.5mm for default.
// This means particle entering DWC1 at (x mm, y mm) should enter DWC2 at (x +- 1.5 mm, y +-1.5 mm)
bool dwcCorrelationCut(std::vector<float> dwc1_correctedPosition, std::vector<float> dwc2_correctedPosition, float threshold = 1.5f) {
    bool passed = false;

    float x_diff = std::abs( dwc1_correctedPosition.at(0) - dwc2_correctedPosition.at(0) );
    float y_diff = std::abs( dwc1_correctedPosition.at(1) - dwc2_correctedPosition.at(1) );

    if ( (x_diff <= threshold) && (y_diff <= threshold) ) passed = true;

    return passed;
}

//////////////////////////////////////////////////////////////////////////////
// print progress
//////////////////////////////////////////////////////////////////////////////

// Simple utility to print progress
void printProgress(const int currentStep, const int totalStep)
{
    // print progress
    float progress = (float)currentStep / totalStep;
    int barWidth = 70;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; i++)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "]  " << currentStep << "/" << totalStep << "  " << int(progress * 100.0) << "%\r";
    std::cout.flush();
}


std::map<std::string, std::vector<int>> getModuleConfigMap() {
    std::map<std::string, std::vector<int>> map_btw_MIDCH_and_Name;

    for(int i = 1; i <= 20; i++) {
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"01",  std::vector<int>  {i, 1}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"02",  std::vector<int>  {i, 2}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"03",  std::vector<int>  {i, 3}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"04",  std::vector<int>  {i, 4}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"05",  std::vector<int>  {i, 5}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"06",  std::vector<int>  {i, 6}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"07",  std::vector<int>  {i, 7}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"08",  std::vector<int>  {i, 8}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"09",  std::vector<int>  {i, 9}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"10",  std::vector<int>  {i, 10}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"11",  std::vector<int>  {i, 11}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"12",  std::vector<int>  {i, 12}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"13",  std::vector<int>  {i, 13}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"14",  std::vector<int>  {i, 14}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"15",  std::vector<int>  {i, 15}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"16",  std::vector<int>  {i, 16}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"17",  std::vector<int>  {i, 17}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"18",  std::vector<int>  {i, 18}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"19",  std::vector<int>  {i, 19}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"20",  std::vector<int>  {i, 20}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"21",  std::vector<int>  {i, 21}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"22",  std::vector<int>  {i, 22}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"23",  std::vector<int>  {i, 23}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"24",  std::vector<int>  {i, 24}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"25",  std::vector<int>  {i, 25}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"26",  std::vector<int>  {i, 26}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"27",  std::vector<int>  {i, 27}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"28",  std::vector<int>  {i, 28}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"29",  std::vector<int>  {i, 29}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"30",  std::vector<int>  {i, 30}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"31",  std::vector<int>  {i, 31}));
      map_btw_MIDCH_and_Name.insert(std::make_pair( std::to_string(i)+"32",  std::vector<int>  {i, 32}));
    }
    return map_btw_MIDCH_and_Name;
}