#include "TBread.h"
#include "TButility.h"

#include "../preset.h"


#include <TString.h>
#include <TH1D.h>

#include <vector>
#include <string>
#include <cmath> // -- for std::sqrt


class DRCFiber {
public:
  // -- type: c or s (C or S is also allowed)
  DRCFiber(TButility& util, int moduleNum, int towerNum, std::string type):
  moduleNum_(moduleNum), towerNum_(towerNum), type_(type) { Init(util); }

  // -- get waveform
  std::vector<short> Get_Wave(TBevt<TBwaveform>* anEvt) {
    anEvt->GetData( cid_.waveform() );
  }

  // -- count the waveform of this event (for average time structure at the end)
  void Count_Wave(TBevt<TBwaveform>* anEvt) {
    nProcEvent_++;
    std::vector<short> waveform_thisEvt = Get_Wave(anEvt);
    for(int i=0; i<TB2024::nADCBin; ++i) {
      sum_waveform_[i]     += waveform_thisEvt[i];
      sumSqrt_waveform_[i] += waveform_thisEvt[i]*waveform_thisEvt[i];
    }
  }

  // -- ATS = averaged time structure
  // -- should be called after processing all events (with Count_Wave() per event)
  std::vector<short> Get_ATS() {
    if( nProcEvent_ == 0 )
      throw std::runtime_error("[DRCFiber::Get_ATS] # processed events = 0!");

    if( averaged_ ) {
      cout << "[DRCFiber::Get_ATS] Average is already calculated... return it";
      return avg_waveform_;
    }

    for(int i=0; i<TB2024::nADCBin; ++i) {
      avg_waveform_[i] = sum_waveform_[i] / nProcEvent_;
      stdDev_waveform_[i] = std::sqrt(sumSqrt_waveform_[i]/nProcEvent_ - avg_waveform_[i]*avg_waveform_[i]); // -- <X^2> - <X>^2
    }
    averaged_ = kTRUE;

    return avg_waveform_; // -- return the central value only
  }

  TH1D* GetHist_ATS() {
    std::vector<short> avg_waveform = Get_ATS();

    TString histName = "h_ats_"+tag_;
    TH1D* h_ats = new TH1D(histName, "", 0, TB2024::nADCBin, TB2024::nADCBin);
    for(int i=0; i<TB2024::nADCBin; ++i) {
      int i_bin = i+1;
      h_ats->SetBinContent(i_bin, avg_waveform_[i]);
      h_ats->SetBinError(i_bin, stdDev_waveform_[i]); // -- std. dev
    }

    return h_ats;
  }

private:
  int moduleNum_ = 0;
  int towerNum_ = 0;
  std::string type_ = "undefined";

  TString tag_ = "undefined";
  TBcid cid_;

  // -- for avg. time structure
  int nProcEvent_; // -- # processed events
  std::vector<short> sum_waveform_;
  std::vector<short> sumSqrt_waveform_; // -- for std. dev.
  std::vector<short> avg_waveform_;
  std::vector<short> stdDev_waveform_;
  bool averaged_ = kFALSE;

  void Init(TButility& util) {
    BasicCheck();

    tag_ = MakeTag();
    cid_ = util.GetCID(tag_);

    // -- init. sum of waveform
    nProcEvent_ = 0;
    averaged_ = kFALSE;
    for(int i=0; i<TB2024::nADCBin; ++i) {
      sum_waveform_[i] = 0;
      sumSqrt_waveform_[i] = 0;
      avg_waveform_[i] = 0;
    }
  }

  TString MakeTag() {
    TString fiberTag = type_;
    if( fiberTag == "c" ) fiberTag = "C";
    if( fiberTag == "s" ) fiberTag = "S";
    return "M"+std::to_string(moduleNum_)+"-T"+std::to_string(towerNum_)+"-"+fiberTag.Data(); // -- e.g. M1-T2-C;
  }

  void BasicCheck() {
    if( fiber == "C" ) fiber = "c";
    if( fiber == "S" ) fiber = "s";

    if( !(fiber == "c" || fiber == "s") )
      throw std::invalid_argument("[DRCFiber::BasicCheck] no fiber corresponding to " + fiber);
  }
};