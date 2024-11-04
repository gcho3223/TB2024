#include "DRCModule.h"

class DRC {
public:
  DRC(TButility& util, int nTotModule = 9): nTotModule_(nTotModule) { Init(util); }

  DRCModule& Get_Module(int moduleNum) {
    auto iter = map_module_.find(moduleNum);
    if( iter == map_module_.end() )
      throw std::invalid_argument("[DRCModule::Get_Module] no module corresponding to " + moduleNum);

    return iter->second;
  }

  int nModule() { return nTotModule_; }

  void Update(TBevt<TBwaveform>* anEvt) {
    for(auto& pair : map_module_ )
      pair.second.Update(anEvt);
  }

  double Get_EnergySum(TString fiberType, bool applySF=kTRUE) {
    double sum = 0;
    for(auto& pair : map_module_ )
      sum += pair.second.Get_EnergySum(fiberType, applySF);

    return sum;
  }

  // -- map_towerNum: (moduleNum, vec_towerNum) pairs
  double Get_PartialEnergySum(std::map<int, std::vector<int>>& map_towerNum, TString fiberType, bool applySF=kTRUE) {
    double sum = 0;
    for(auto& pair : map_towerNum ) {
      int moduleNum = pair.first;
      DRCModule& module_i = Get_Module(moduleNum);

      const std::vector<int>& vec_towerNum = pair.second;
      for(auto& towerNum : vec_towerNum )
        sum += module_i.Get_Tower(towerNum).Get_EnergySum(fiberType, applySF);
    }

    return sum;
  }

private:
  int nTotModule_;
  std::map<int, DRCModule> map_module_;

  void Init(TButility& util) {
    if( nTotModule_ > 11 )
      throw std::invalid_argument("[DRC::Init] nTotModule = " + std::to_string(nTotModule_) + " is not supported");

    for(int i=0; i<nTotModule_; ++i) {
      int i_module = i+1; // -- start from 1
      // std::cout << "module " << i_module << std::endl;

      map_module_.insert( std::make_pair(i_module, DRCModule(util, i_module)) );
    }
  }
};