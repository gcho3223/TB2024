#include "TBread.h"
#include "TButility.h"

#include "../preset.h"
#include "../ATS.h"
#include "../../function.h"

#include <TString.h>
#include <TH1D.h>

#include <vector>
#include <string>
#include <iostream>


class DRCFiber {
public:
  DRCFiber() { }

  // -- type: c or s
  DRCFiber(TButility& util, int moduleNum, int towerNum, std::string type):
  moduleNum_(moduleNum), towerNum_(towerNum), type_(type) { Init(util); }

  TString Tag() { return tag_; }

  // -- update the member variables corresponding to this event
  void Update(TBevt<TBwaveform>* anEvt) {
    waveform_ = Get_Waveform(anEvt);
    peakADC_  = GetPeak(waveform_, intRange_.first, intRange_.second);
    intADC_   = GetInt(waveform_, intRange_.first, intRange_.second);
    energy_noSF_ = intADC_ * calibConst_;
    // -- remove negative values
    if( energy_noSF_ < 0 ) energy_noSF_ = 0;

    energy_ = energy_noSF_ * sf_;
  }

  std::vector<short> Get_Wave() { return waveform_; }
  double Get_PeakADC() { return peakADC_; }
  double Get_IntADC()  { return intADC_; }
  double Get_Energy(bool applySF=kTRUE) { return applySF ? energy_ : energy_noSF_; }

  // -- count the waveform of this event (for average time structure at the end)
  void Count_Wave() { ats_.Fill(waveform_); }

  // -- ATS = averaged time structure
  // -- should be called after processing all events (with Count_Wave() per event)
  std::vector<double> Get_ATS() { return ats_.Get(); }

  TH1D* GetHist_ATS() { return ats_.GetHist(tag_); }

private:
  int moduleNum_ = 0;
  int towerNum_ = 0;
  std::string type_ = "undefined";

  TString tag_ = "undefined";
  TBcid cid_;

  ATS ats_; // -- average time structure

  std::pair<int, int> intRange_;
  double calibConst_ = -1;
  double sf_ = 1.0;

  // -- values for a given event
  // -- updated whenever Update() is called
  std::vector<short> waveform_;
  double peakADC_;
  double intADC_;
  double energy_noSF_;
  double energy_;

  void Init(TButility& util) {
    BasicCheck();

    tag_ = MakeTag();
    cid_ = util.GetCID(tag_);
    ats_ = ATS();

    intRange_ = TB2024::GetIntRange_DRC(tag_);
    calibConst_ = TB2024::map_calibConst[tag_];
    if( calibConst_ <= 0 )
      throw std::invalid_argument("no calib. const. for the fiber = " + tag_);

    sf_ = TB2024::map_sf_[type_];
  }

  TString MakeTag() {
    TString fiberTag = type_;
    if( fiberTag == "c" ) fiberTag = "C";
    if( fiberTag == "s" ) fiberTag = "S";
    return "M"+std::to_string(moduleNum_)+"-T"+std::to_string(towerNum_)+"-"+fiberTag.Data(); // -- e.g. M1-T2-C;
  }

  void BasicCheck() {
    if( !(type_ == "c" || type_ == "s") )
      throw std::invalid_argument("[DRCFiber::BasicCheck] no fiber corresponding to " + type_);
  }

  // -- get waveform
  std::vector<short> Get_Waveform(TBevt<TBwaveform>* anEvt) {
    return anEvt->GetData(cid_).waveform();
  }
};