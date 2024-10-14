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
  // -- type: c or s (C or S is also allowed)
  DRCFiber(TButility& util, int moduleNum, int towerNum, std::string type):
  moduleNum_(moduleNum), towerNum_(towerNum), type_(type) { Init(util); }

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

private:
  int moduleNum_ = 0;
  int towerNum_ = 0;
  std::string type_ = "undefined";

  TString tag_ = "undefined";
  TBcid cid_;

  ATS ats_; // -- average time structure

  std::pair<int, int> intRange_;

  void Init(TButility& util) {
    BasicCheck();

    tag_ = MakeTag();
    cid_ = util.GetCID(tag_);
    ats_ = ATS();

    intRange_ = TB2024::GetIntRange_DRC(tag_);
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
};