#include <map>
#include <iostream>

#include <TString.h>

namespace TB2024 {

void PrintMap(TString type, std::map<TString, double>& map) {
  printf("Print %s ...\n", type.Data());

  for(auto& pair : map ) {
    printf("(%s, %lf)\n", pair.first.Data(), pair.second);
  }
  printf("\n");
}

void Print_SF(std::map<TString, double>& map_sf) {
  PrintMap("customized scale factor", map_sf);
}

};