#pragma once

#include <TString.h>

#include <vector>

namespace TB2024 {
  std::vector<int> vec_calibRun = {
    10458, 10459, 10457, 10456, // -- M1, T1-4
    10460, 10463, 10461, 10462,
    10464, 10465, 10467, 10466,
    10450, 10451, 10449, 10448,
    10482, 10483, 10481, 10480,
    10468, 10469, 10479, 10470, 
    10444, 10447, 10445, 10446,
    10476, 10477, 10475, 10474,
    10478, 10471, 10473, 10472, // -- M9, T1-4
  };

  std::map<TString, int> GetMap_CalibRun() {
    std::map<TString, int> map_calibRun;
    int nRun = (int)vec_calibRun.size();
    for(int i_run=0; i_run<nRun; ++i_run) {
      int moduleNum = (int)(i_run/4)+1;
      int towerNum = (i_run%4) + 1;

      TString tag = TString::Format("M%d-T%d", moduleNum, towerNum);
      map_calibRun.insert( std::make_pair(tag, vec_calibRun[i_run]) );
    }

    // -- print
    for(auto& pair : map_calibRun )
      printf("%s --> %d\n", pair.first.Data(), pair.second);

    return map_calibRun;
  }

  std::map<TString, int> map_muBeamRun = {
    {"Top",           10509},
    {"Bottom",        10503},
    {"Left(Jura)",    10505},
    {"Right(Saleve)", 10507},
  };

  std::vector<double> vec_emScanE = {10, 20, 30, 40, 60, 80, 100};
  // std::vector<int> vec_emScanRun = {
  //   10547, 10555, 10554, 10557, 10533, 10556, 10553, // -- M5T1
  //   10548, 10552, 10551, 10550, 10535, 10545, 10549, // -- M5T3
  //   10560, 10562, 10561, 10559, 10538, 10544, 10558, // -- M8T2
  //   10571, 10570, 10569, 10568, 10540, 10543, 10567, // -- M9T1
  // }
  std::map<TString, std::vector<int>> map_emScanRun = {
    {"M5-T1", {10547, 10555, 10554, 10557, 10533, 10556, 10553}},
    {"M5-T3", {10548, 10552, 10551, 10550, 10535, 10545, 10549}},
    {"M8-T2", {10560, 10562, 10561, 10559, 10538, 10544, 10558}},
    {"M9-T1", {10571, 10570, 10569, 10568, 10540, 10543, 10567}},
  };
  
}; // -- namespace TB2024