// -- define basic values used over the analysis
#pragma once

#include <utility> // -- include pair

namespace TB2024 {
  int nADCBin = 1000;

  /////////////////////////////
  // -- integration range -- //
  /////////////////////////////

  // ---- DRC: common range (200, 400): simlar to PA
  std::pair<int, int> intRange_drc_default = std::pair<int, int>(200, 400);
  std::pair<int, int> intRange_drc_M5   = std::pair<int, int>(200, 400);
  std::pair<int, int> intRange_drc_M5T3 = std::pair<int, int>(200, 400);

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
    {"M1-T1-C", 0.000763},
    {"M1-T1-S", 0.000598},
    {"M1-T2-C", 0.000822},
    {"M1-T2-S", 0.000553},
    {"M1-T3-C", 0.000867},
    {"M1-T3-S", 0.000450},
    {"M1-T4-C", 0.000806},
    {"M1-T4-S", 0.000531},
    {"M2-T1-C", 0.000816},
    {"M2-T1-S", 0.000552},
    {"M2-T2-C", 0.000790},
    {"M2-T2-S", 0.000535},
    {"M2-T3-C", 0.000852},
    {"M2-T3-S", 0.000552},
    {"M2-T4-C", 0.000821},
    {"M2-T4-S", 0.000547},
    {"M3-T1-C", 0.000804},
    {"M3-T1-S", 0.000555},
    {"M3-T2-C", 0.000807},
    {"M3-T2-S", 0.000535},
    {"M3-T3-C", 0.000823},
    {"M3-T3-S", 0.000534},
    {"M3-T4-C", 0.000819},
    {"M3-T4-S", 0.000544},
    {"M4-T1-C", 0.000810},
    {"M4-T1-S", 0.000524},
    {"M4-T2-C", 0.000847},
    {"M4-T2-S", 0.000547},
    {"M4-T3-C", 0.000836},
    {"M4-T3-S", 0.000564},
    {"M4-T4-C", 0.000789},
    {"M4-T4-S", 0.000545},
    {"M5-T1-C", 0.000816},
    {"M5-T1-S", 0.000507},
    {"M5-T2-C", 0.000840},
    {"M5-T2-S", 0.000483},
    {"M5-T3-C", 0.001177},
    {"M5-T3-S", 0.000838},
    {"M5-T4-C", 0.000784},
    {"M5-T4-S", 0.000524},
    {"M6-T1-C", 0.000810},
    {"M6-T1-S", 0.000596},
    {"M6-T2-C", 0.000792},
    {"M6-T2-S", 0.000573},
    {"M6-T3-C", 0.000806},
    {"M6-T3-S", 0.000567},
    {"M6-T4-C", 0.000821},
    {"M6-T4-S", 0.000621},
    {"M7-T1-C", 0.000792},
    {"M7-T1-S", 0.000502},
    {"M7-T2-C", 0.000808},
    {"M7-T2-S", 0.000547},
    {"M7-T3-C", 0.000829},
    {"M7-T3-S", 0.000552},
    {"M7-T4-C", 0.000847},
    {"M7-T4-S", 0.000551},
    {"M8-T1-C", 0.000823},
    {"M8-T1-S", 0.000551},
    {"M8-T2-C", 0.000848},
    {"M8-T2-S", 0.000541},
    {"M8-T3-C", 0.000839},
    {"M8-T3-S", 0.000558},
    {"M8-T4-C", 0.000799},
    {"M8-T4-S", 0.000530},
    {"M9-T1-C", 0.000762},
    {"M9-T1-S", 0.000561},
    {"M9-T2-C", 0.000837},
    {"M9-T2-S", 0.000558},
    {"M9-T3-C", 0.000819},
    {"M9-T3-S", 0.000584},
    {"M9-T4-C", 0.000783},
    {"M9-T4-S", 0.000588},
  };

  std::map<TString, double> map_sf = {
    {"c", 0.771253},
    {"s", 0.778751},
  };

}; // -- end of namespace TB2024