#include "../preset.h"
#include "DRCFiber.h"

#include <map>

class DRCTower {
public:
  DRCTower(TButility& util, int moduleNum, int towerNum):
  moduleNum_(moduleNum), towerNum_(towerNum) { Init(util); }

  DRCFiber& Get_Fiber(std::string fiber) {
    auto iter = map_fiber_.find(fiber);
    if( iter == map_fiber_.end() )
      throw std::invalid_argument("[DRCModule::Get_Fiber] no fiber corresponding to " + fiber);

    return iter->second;
  }

  std::vector<short> Get_Wave(TBevt<TBwaveform>* anEvt, std::string fiber) { 
    return Get_Fiber(fiber).Get_Wave(anEvt); 
  }

  void Count_Wave(TBevt<TBwaveform>* anEvt) {
    for(auto& pair : map_fiber_ )
      pair.second.Count_Wave(anEvt);
  }

  std::vector<short> Get_ATS(std::string fiber) {
    return Get_Fiber(fiber).Get_ATS(); 
  }

private:
  int moduleNum_ = 0;
  int towerNum_ = 0;

  std::map<std::string, DRCFiber> map_fiber_;

  void Init(TButility& util) {
    BasicCheck();

    // -- init. DRCFiber
    vector<std::string> vec_fiberType = {"c", "s"};
    for( auto& type : vec_fiberType )
      map_fiber_.insert( std::make_pair(type, DRCFiber(util, moduleNum_, towerNum_, type)) );
  }

  void BasicCheck() {
    if( moduleNum_ > 11 )
      throw std::invalid_argument("[DRCTower::BasicCheck] moduleNum = " + std::to_string(moduleNum_) + " > 11!");

    if( moduleNum_ <= 9 && towerNum_ > 4 )
      throw std::invalid_argument("[DRCTower::BasicCheck] towerNum_ = " + std::to_string(towerNum__) + " > 4!");
  }
};