#pragma once

#include "TBread.h"
#include "TButility.h"

#include "../../function.h"

#include "../preset.h"
#include "../ATS.h"

class AuxDetector {
public:
  AuxDetector(TButility& util, TString tag): tag_(tag) { Init(util); }

  // -- get waveform
  std::vector<short> Get_Wave(TBevt<TBwaveform>* anEvt) {
    return anEvt->GetData(cid_).waveform();
  }

  // -- count the waveform of this event (for average time structure at the end)
  void Count_Wave(TBevt<TBwaveform>* anEvt) {
    std::vector<short> waveform_thisEvt = Get_Wave(anEvt);
    ats_.Fill(waveform_thisEvt);
  }

  // -- ATS = averaged time structure
  // -- should be called after processing all events (with Count_Wave() per event)
  std::vector<double> Get_ATS() { return ats_.Get(); }
  TH1D* GetHist_ATS() { return ats_.GetHist(tag_); }

  TString Tag() { return tag_; }
  double Get_PeakADC(TBevt<TBwaveform>* anEvt) { return GetPeak(Get_Wave(anEvt), intRange_.first, intRange_.second); }
  double Get_IntADC(TBevt<TBwaveform>* anEvt) { return GetInt(Get_Wave(anEvt), intRange_.first, intRange_.second); }

  bool Pass(TBevt<TBwaveform>* anEvt) {
    double peakADC = Get_PeakADC(anEvt);

    // printf("[%s] peakADC = %lf, cut = (%f, %f)\n", tag_.Data(), peakADC, cut_.first, cut_.second);

    if( !(cut_.first <= peakADC && peakADC <= cut_.second) ) return kFALSE;
    return kTRUE;
  }

private:
  TString tag_;
  TBcid cid_;

  ATS ats_; // -- average time structure

  std::pair<int, int> intRange_;
  std::pair<float, float> cut_;

  void Init(TButility& util) {
    cid_ = util.GetCID(tag_);
    ats_ = ATS();

    intRange_ = TB2024::GetIntRange_Aux(tag_);
    cut_      = TB2024::GetCut_Aux(tag_);
  }
};