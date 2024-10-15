#include "DRCFiber.h"

#include <map>

class DRCTower {
public:
  DRCTower(TButility& util, int moduleNum, int towerNum):
  moduleNum_(moduleNum), towerNum_(towerNum) { Init(util); }

  TString Tag() { return tag_; }

  DRCFiber& Get_Fiber(std::string fiber) {
    auto iter = map_fiber_.find(fiber);
    if( iter == map_fiber_.end() )
      throw std::invalid_argument("[DRCModule::Get_Fiber] no fiber corresponding to " + fiber);

    return iter->second;
  }

  void Update(TBevt<TBwaveform>* anEvt) {
    for(auto& pair : map_fiber_ )
      pair.second.Update(anEvt);
  }

  double Get_EnergySum(TString fiberType, bool applySF=kTRUE) {
    double sum = 0;

    if( fiberType == "c" || fiberType == "s" ) 
      sum = map_fiber_[fiberType.Data()].Get_Energy(applySF);
    else if( fiberType == "all" ) { // -- S+C;
      for(auto& pair : map_fiber_ )
        sum += pair.second.Get_Energy(applySF);
    }
    else
      throw std::invalid_argument("[DRCTower::Get_EnergySum] fiberType = " + fiberType + " is not supported");

    return sum;
  }

private:
  int moduleNum_ = 0;
  int towerNum_ = 0;
  TString tag_ = "undefined";

  std::map<std::string, DRCFiber> map_fiber_;

  void Init(TButility& util) {
    BasicCheck();

    tag_ = TString::Format("M%d-T%d", moduleNum_, towerNum_);

    // -- init. DRCFiber
    std::vector<std::string> vec_fiberType = {"c", "s"};
    for( auto& type : vec_fiberType )
      map_fiber_.insert( std::make_pair(type, DRCFiber(util, moduleNum_, towerNum_, type)) );
  }

  void BasicCheck() {
    if( moduleNum_ > 11 )
      throw std::invalid_argument("[DRCTower::BasicCheck] moduleNum = " + std::to_string(moduleNum_) + " > 11!");

    if( moduleNum_ <= 9 && towerNum_ > 4 )
      throw std::invalid_argument("[DRCTower::BasicCheck] towerNum_ = " + std::to_string(towerNum_) + " > 4!");
  }
};