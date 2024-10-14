#pragma once

#include "preset.h"

#include <TH1D.h>
#include <TString.h>

#include <vector>
#include <cmath> // -- for std::sqrt

// -- hold information to calculate average time structure
class ATS {
public:
  ATS() { Init(); }

  void Fill(std::vector<short>& waveform) {
    nProcEvent_++;
    for(int i=0; i<TB2024::nADCBin; ++i) {
      sum_waveform_[i]   += (double)waveform[i+1]; // -- shift by 1 (ignore the first bin of the waveform; sometimes unreliable values there)
      sumSq_waveform_[i] += (double)waveform[i+1]*waveform[i+1];
    }
  }

  // -- should be called after running over all events
  std::vector<double> Get() {
    if( !averaged_ ) Calc_Average();

    return avg_waveform_; // -- return the central value only
  }

  TH1D* GetHist(TString histTag) {
    if( !averaged_ ) Calc_Average();

    TString histName = "h_ats_"+histTag;
    TH1D* h_ats = new TH1D(histName, "", TB2024::nADCBin, 0, TB2024::nADCBin);
    for(int i=0; i<TB2024::nADCBin; ++i) {
      int i_bin = i+1;
      h_ats->SetBinContent(i_bin, avg_waveform_[i]);
      h_ats->SetBinError(i_bin, stdDev_waveform_[i]); // -- std. dev
    }
    return h_ats;
  }

private:
  // -- for avg. time structure
  // -- FIXME: there should be a better way rather than using 4 different vectors...
  int nProcEvent_; // -- # processed events
  std::vector<double> sum_waveform_; // -- sum or avg. shoule be "double (float)", not short
  std::vector<double> sumSq_waveform_; // -- sqaure sum: for std. dev.
  std::vector<double> avg_waveform_;
  std::vector<double> stdDev_waveform_;
  bool averaged_ = kFALSE;

  void Init() {
    // -- init. sum of waveform
    nProcEvent_ = 0;
    averaged_ = kFALSE;
    
    sum_waveform_     = std::vector<double>(TB2024::nADCBin, 0);
    sumSq_waveform_   = std::vector<double>(TB2024::nADCBin, 0);
    avg_waveform_     = std::vector<double>(TB2024::nADCBin, 0);
    stdDev_waveform_  = std::vector<double>(TB2024::nADCBin, 0);
  }

  void Calc_Average() {
    if( nProcEvent_ == 0 )
      throw std::runtime_error("[ATS::Calc_Average] # processed events = 0!");

    if( averaged_ ) {
      std::cout << "[ATS::Calc_Average] Average is already calculated... do nothing" << std::endl;
      return;
    }

    for(int i=0; i<TB2024::nADCBin; ++i) {
      avg_waveform_[i] = sum_waveform_[i] / nProcEvent_;
      stdDev_waveform_[i] = std::sqrt(sumSq_waveform_[i]/nProcEvent_ - avg_waveform_[i]*avg_waveform_[i]); // -- sqrt(<X^2> - <X>^2)
    }
    averaged_ = kTRUE;
  }
};