#include "DRCTower.h"

class DRCModule {
public:
  DRCModule(TButility& util, int moduleNum): moduleNum_(moduleNum) { Init(util); }

  DRCTower& Get_Tower(int towerNum) {
    auto iter = map_tower_.find(towerNum);
    if( iter == map_tower_.end() )
      throw std::invalid_argument("[DRCModule::Get_Tower] no tower corresponding to " + towerNum);

    return iter->second;
  }

private:
  int moduleNum_ = 0;
  std::map<int, DRCTower> map_tower_;

  void Init(TButility& util) {
    int nTower;
    if( moduleNum_ >= 10 ) nTower = 9;
    else                   nTower = 4;

    for(int i=0; i<nTower; ++i) {
      int i_tower = i+1; // -- start from 1
      // std::cout << "tower " << i_tower << std::endl;
      map_tower_.insert( std::make_pair(i_tower, DRCTower(util, moduleNum_, i_tower)) );
    }
  }
};