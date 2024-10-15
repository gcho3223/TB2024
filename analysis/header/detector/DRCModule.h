#include "DRCTower.h"

class DRCModule {
public:
  DRCModule(TButility& util, int moduleNum): moduleNum_(moduleNum) { Init(util); }

  TString Tag() { return tag_; }

  DRCTower& Get_Tower(int towerNum) {
    auto iter = map_tower_.find(towerNum);
    if( iter == map_tower_.end() )
      throw std::invalid_argument("[DRCModule::Get_Tower] no tower corresponding to " + towerNum);

    return iter->second;
  }

  void Update(TBevt<TBwaveform>* anEvt) {
    for(auto& pair : map_tower_ )
      pair.second.Update(anEvt);
  }

  double Get_EnergySum(TString fiberType, bool applySF=kTRUE) {
    double sum = 0;
    for(auto& pair : map_tower_ )
      sum += pair.second.Get_EnergySum(fiberType, applySF);

    return sum;
  }

  int nTower() { return nTower_; }

private:
  int moduleNum_ = 0;
  TString tag_ = "undefined";

  int nTower_;
  std::map<int, DRCTower> map_tower_;


  void Init(TButility& util) {
    if( moduleNum_ >= 10 ) nTower_ = 9;
    else                   nTower_ = 4;

    tag_ = TString::Format("M%d", moduleNum_);

    for(int i=0; i<nTower_; ++i) {
      int i_tower = i+1; // -- start from 1
      // std::cout << "tower " << i_tower << std::endl;
      map_tower_.insert( std::make_pair(i_tower, DRCTower(util, moduleNum_, i_tower)) );
    }
  }
};