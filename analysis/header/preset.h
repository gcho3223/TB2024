// -- define basic values used over the analysis
#pragma once

#include <utility> // -- include pair

namespace TB2024 {
  int nADCBin = 1000;

  /////////////////////////////
  // -- integration range -- //
  /////////////////////////////

  // ---- DRC
  // std::pair<int, int> intRange_drc_default = std::pair<int, int>(260, 600);
  // std::pair<int, int> intRange_drc_M5   = std::pair<int, int>(200, 540); // -- shift by 60
  // std::pair<int, int> intRange_drc_M5T3 = std::pair<int, int>(200, 500); // -- MCP-PMT; shaper shape
  // -- tighter range
  std::pair<int, int> intRange_drc_default = std::pair<int, int>(260, 460);
  std::pair<int, int> intRange_drc_M5   = std::pair<int, int>(200, 400); // -- shift by 60
  std::pair<int, int> intRange_drc_M5T3 = std::pair<int, int>(180, 360); // -- MCP-PMT; shaper shape

  std::pair<int, int> GetIntRange_DRC(TString tag) {
    if( tag.BeginsWith("M5-") ) {
      if( tag.BeginsWith("M5-T3") ) return intRange_drc_M5T3;
      else                          return intRange_drc_M5;
    }

    // -- other modules/towers: use default value
    return intRange_drc_default;
  }

  // ---- aux. detectors
  std::pair<int, int> intRange_ps  = std::pair<int, int>(320, 440);
  std::pair<int, int> intRange_mc  = std::pair<int, int>(720, 880);
  std::pair<int, int> intRange_dwc = std::pair<int, int>(0, 1000); // -- dummy (not used anyway)

  std::pair<int, int> GetIntRange_Aux(TString tag) {
    if( tag == "PS" )              return intRange_ps;
    else if( tag == "MC" )         return intRange_mc;
    else if( tag.Contains("DWC") ) return intRange_dwc;
    else
      throw std::invalid_argument("[GetIntRange_Aux] tag = " + tag + " is not recognized");

    return std::pair<int, int>(0, 0);
  }

  /////////////////////////////////////////// 
  // -- event selection (EM resolution) -- //
  ///////////////////////////////////////////
  std::pair<float, float> cut_DWC_size = std::pair<float, float>(-5.0, 5.0);
  std::pair<float, float> cut_DWC_diff_x = std::pair<float, float>(0, 4); // -- difference between two DWC positions (x)
  std::pair<float, float> cut_DWC_diff_y = std::pair<float, float>(0, 4); // -- difference between two DWC positions (y)

  std::pair<float, float> cut_PS = std::pair<float, float>(700, 1e5);
  std::pair<float, float> cut_MC = std::pair<float, float>(0, 40);
  std::pair<int, int> GetCut_Aux(TString tag) {
    if( tag == "PS" )              return cut_PS;
    else if( tag == "MC")          return cut_MC;
    else if( tag.Contains("DWC") ) return std::pair<int, int>(0, 0); // -- dummy (not used)
    else
      throw std::invalid_argument("[GetCut_Aux] tag = " + tag + " is not recognized");

    return std::pair<int, int>(0, 0);
  }

  std::map<TString, double> map_calibConst = {
    // {"M1-T1-C", 0.000636},
    // {"M1-T1-S", 0.000482},
    // {"M1-T2-C", 0.000726},
    // {"M1-T2-S", 0.000460},
    // {"M1-T3-C", 0.000760},
    // {"M1-T3-S", 0.000369},
    // {"M1-T4-C", 0.000715},
    // {"M1-T4-S", 0.000436},
    // {"M2-T1-C", 0.000718},
    // {"M2-T1-S", 0.000436},
    // {"M2-T2-C", 0.000693},
    // {"M2-T2-S", 0.000426},
    // {"M2-T3-C", 0.000748},
    // {"M2-T3-S", 0.000436},
    // {"M2-T4-C", 0.000723},
    // {"M2-T4-S", 0.000437},
    // {"M3-T1-C", 0.000715},
    // {"M3-T1-S", 0.000393},
    // {"M3-T2-C", 0.000716},
    // {"M3-T2-S", 0.000429},
    // {"M3-T3-C", 0.000732},
    // {"M3-T3-S", 0.000429},
    // {"M3-T4-C", 0.000731},
    // {"M3-T4-S", 0.000431},
    // {"M4-T1-C", 0.000695},
    // {"M4-T1-S", 0.000430},
    // {"M4-T2-C", 0.000762},
    // {"M4-T2-S", 0.000449},
    // {"M4-T3-C", 0.000742},
    // {"M4-T3-S", 0.000459},
    // {"M4-T4-C", 0.000700},
    // {"M4-T4-S", 0.000453},
    // {"M5-T1-C", 0.000777},
    // {"M5-T1-S", 0.000474},
    // {"M5-T2-C", 0.000805},
    // {"M5-T2-S", 0.000450},
    // {"M5-T3-C", 0.001163},
    // {"M5-T3-S", 0.000805},
    // {"M5-T4-C", 0.000750},
    // {"M5-T4-S", 0.000488},
    // {"M6-T1-C", 0.000727},
    // {"M6-T1-S", 0.000452},
    // {"M6-T2-C", 0.000710},
    // {"M6-T2-S", 0.000453},
    // {"M6-T3-C", 0.000715},
    // {"M6-T3-S", 0.000453},
    // {"M6-T4-C", 0.000736},
    // {"M6-T4-S", 0.000493},
    // {"M7-T1-C", 0.000684},
    // {"M7-T1-S", 0.000407},
    // {"M7-T2-C", 0.000722},
    // {"M7-T2-S", 0.000460},
    // {"M7-T3-C", 0.000742},
    // {"M7-T3-S", 0.000458},
    // {"M7-T4-C", 0.000755},
    // {"M7-T4-S", 0.000459},
    // {"M8-T1-C", 0.000707},
    // {"M8-T1-S", 0.000456},
    // {"M8-T2-C", 0.000760},
    // {"M8-T2-S", 0.000446},
    // {"M8-T3-C", 0.000751},
    // {"M8-T3-S", 0.000464},
    // {"M8-T4-C", 0.000711},
    // {"M8-T4-S", 0.000442},
    // {"M9-T1-C", 0.000674},
    // {"M9-T1-S", 0.000438},
    // {"M9-T2-C", 0.000747},
    // {"M9-T2-S", 0.000412},
    // {"M9-T3-C", 0.000729},
    // {"M9-T3-S", 0.000456},
    // {"M9-T4-C", 0.000694},
    // {"M9-T4-S", 0.000454},

    // -- from tighter int. range
    {"M1-T1-C", 0.000694},
    {"M1-T1-S", 0.000522},
    {"M1-T2-C", 0.000772},
    {"M1-T2-S", 0.000489},
    {"M1-T3-C", 0.000814},
    {"M1-T3-S", 0.000396},
    {"M1-T4-C", 0.000758},
    {"M1-T4-S", 0.000468},
    {"M2-T1-C", 0.000764},
    {"M2-T1-S", 0.000472},
    {"M2-T2-C", 0.000739},
    {"M2-T2-S", 0.000461},
    {"M2-T3-C", 0.000798},
    {"M2-T3-S", 0.000472},
    {"M2-T4-C", 0.000766},
    {"M2-T4-S", 0.000473},
    {"M3-T1-C", 0.000756},
    {"M3-T1-S", 0.000441},
    {"M3-T2-C", 0.000761},
    {"M3-T2-S", 0.000465},
    {"M3-T3-C", 0.000775},
    {"M3-T3-S", 0.000465},
    {"M3-T4-C", 0.000771},
    {"M3-T4-S", 0.000467},
    {"M4-T1-C", 0.000747},
    {"M4-T1-S", 0.000461},
    {"M4-T2-C", 0.000800},
    {"M4-T2-S", 0.000482},
    {"M4-T3-C", 0.000788},
    {"M4-T3-S", 0.000494},
    {"M4-T4-C", 0.000743},
    {"M4-T4-S", 0.000483},
    {"M5-T1-C", 0.000816},
    {"M5-T1-S", 0.000507},
    {"M5-T2-C", 0.000840},
    {"M5-T2-S", 0.000483},
    {"M5-T3-C", 0.001198},
    {"M5-T3-S", 0.000870},
    {"M5-T4-C", 0.000784},
    {"M5-T4-S", 0.000524},
    {"M6-T1-C", 0.000769},
    {"M6-T1-S", 0.000494},
    {"M6-T2-C", 0.000751},
    {"M6-T2-S", 0.000492},
    {"M6-T3-C", 0.000765},
    {"M6-T3-S", 0.000491},
    {"M6-T4-C", 0.000782},
    {"M6-T4-S", 0.000535},
    {"M7-T1-C", 0.000737},
    {"M7-T1-S", 0.000439},
    {"M7-T2-C", 0.000767},
    {"M7-T2-S", 0.000493},
    {"M7-T3-C", 0.000788},
    {"M7-T3-S", 0.000493},
    {"M7-T4-C", 0.000804},
    {"M7-T4-S", 0.000494},
    {"M8-T1-C", 0.000762},
    {"M8-T1-S", 0.000491},
    {"M8-T2-C", 0.000803},
    {"M8-T2-S", 0.000479},
    {"M8-T3-C", 0.000795},
    {"M8-T3-S", 0.000499},
    {"M8-T4-C", 0.000755},
    {"M8-T4-S", 0.000473},
    {"M9-T1-C", 0.000717},
    {"M9-T1-S", 0.000477},
    {"M9-T2-C", 0.000791},
    {"M9-T2-S", 0.000452},
    {"M9-T3-C", 0.000773},
    {"M9-T3-S", 0.000495},
    {"M9-T4-C", 0.000736},
    {"M9-T4-S", 0.000492},
  };

  std::map<TString, double> map_sf_ = {
    // {"c", 0.759867},
    // {"s", 0.785475},

    // -- from tighter int. range
    {"c", 0.775657},
    {"s", 0.791671},
  };

}; // -- end of namespace TB2024