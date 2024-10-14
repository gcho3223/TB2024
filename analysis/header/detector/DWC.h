#include "TBread.h"
#include "TButility.h"

#include "AuxDetector.h"

#include "../preset.h"
#include "../ATS.h"
#include "../../function.h"

#include "TH2D.h"

class DWC {
public:
  DWC() { };

  DWC(TButility& util, TString tag): tag_(tag) { Init(util); }

  void Set_Offset(std::vector<float> vec_offset) { vec_offset_ = vec_offset; }

  // -- direction: U, D, R, L
  AuxDetector& Get_SubDWC(TString direction) {
    TString fullTag = tag_+direction; // -- e.g. DWC1U
    auto iter = map_subDWC_.find(fullTag);
    if( iter == map_subDWC_.end() )
      throw std::invalid_argument("[DWC::Get_SubDWC] detector for direction = " + direction + " is not supported");

    return iter->second;
  }

  std::vector<float> Get_LeadingEdgeTime(TBevt<TBwaveform>* anEvt) {
    std::vector<float> vec_time;

    std::vector<TString> vec_direction = {"R", "L", "U", "D"}; // -- the order would be important
    for(auto& direction : vec_direction ) {
      std::vector<short> waveform = Get_SubDWC(direction).Get_Wave(anEvt);
      float time = getLeadingEdgeTime(waveform, 0.4, 1, 1000); // -- 40% edge
      vec_time.emplace_back(time);
    }

    return vec_time;
  }

  std::vector<float> GetPosition_Corr(TBevt<TBwaveform>* anEvt) {
    if( vec_offset_.size() == 0 )
      throw std::runtime_error("[DWC::GetPosition_Corr] offset is not provided! ... use Set_Offset");

    std::vector<float> vec_time = Get_LeadingEdgeTime(anEvt);
    
    std::vector<float> vec_pos_corr;
    if( tag_ == "DWC1" )      vec_pos_corr = getDWC1position(vec_time, vec_offset_);
    else if( tag_ == "DWC2" ) vec_pos_corr = getDWC2position(vec_time, vec_offset_);
    else
      throw std::invalid_argument("[DWC::GetPosition_Corr] tag = " + tag_ + ": don't know which function should be used to get corrected position");

    return vec_pos_corr;
  }

private:
  TString tag_;
  std::vector<TString> vec_subDWCTag_ = {"U", "D", "R", "L"};
  std::map<TString, AuxDetector> map_subDWC_;
  std::vector<float> vec_offset_;

  void Init(TButility& util) {
    
    for( auto& subDWCTag : vec_subDWCTag_ ) {
      TString fullTag = tag_ + subDWCTag; // -- e.g. DWC1U
      map_subDWC_.insert( std::make_pair(fullTag, AuxDetector(util, fullTag)) );
    }
    vec_offset_.clear();
  }
};