// -- define basic values used over the analysis
#pragma once

#include <utility> // -- include pair

namespace TB2024 {
  int nADCBin = 1000;

  /////////////////////////////
  // -- integration range -- //
  /////////////////////////////

  // ---- DRC
  std::pair<int, int> intRange_drc_default = std::pair<int, int>(260, 600);
  std::pair<int, int> intRange_drc_M5   = std::pair<int, int>(200, 540); // -- shift by 60
  std::pair<int, int> intRange_drc_M5T3 = std::pair<int, int>(200, 500); // -- MCP-PMT; shaper shape

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

}; // -- end of namespace TB2024