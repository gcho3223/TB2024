#include "DRCModule.h"

class DRC {
public:
  DRC(TButility& util, int nTotModule = 9) { Init(util); }

  DRCModule& Get_Module(int moduleNum) {
    auto iter = map_module_.find(moduleNum);
    if( iter == map_module_.end() )
      throw std::invalid_argument("[DRCModule::Get_Module] no module corresponding to " + moduleNum);

    return iter->second;
  }

private:
  std::map<int, DRCModule> map_module_;

  void Init(TButility& util) {
    if( nTotModule > 11 )
      throw std::invalid_argument("[DRC::Init] nTotModule = " + std::to_string(nTotModule) + " is not supported");

    for(int i=0; i<nTotModule; ++i) {
      int i_module = i+1; // -- start from 1
      map_module_.insert( std::make_pair(i_module, DRCModule(util, i_module)) );
    }
  }
};