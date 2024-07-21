#ifndef TButility_h
#define TButility_h 1

#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "TBdetector.h"

#include <TChain.h>
#include <TString.h>
#include <TH2.h>
#include <TFile.h>

class TButility
{
public:
  TButility() {}
  ~TButility() {}

  struct mod_info {
    int cases;
    int isCeren;
    int row;
    int col;

    mod_info(int cases_, int isCeren_, int row_, int col_)
    : cases(cases_), isCeren(isCeren_), row(row_), col(col_)
    {}
  };

  void LoadMapping(const std::string &path);

  TBcid GetCID(TString name) const;
  std::string GetName(TBcid cid) const;
  mod_info GetInfo(TBcid cid) const;
  mod_info GetInfo(TString name) const;

  std::vector<int> GetUniqueMID(std::vector<TBcid> aCID) {
    std::vector<int> return_vec;
    std::map<int, int> aMap;

    for (int i = 0; i < aCID.size(); i++) {
      if (aMap.find(aCID.at(i).mid()) == aMap.end()) {
        return_vec.push_back(aCID.at(i).mid());
        aMap.insert(std::make_pair(aCID.at(i).mid(), 1));
      }
    }

    return return_vec;
  }

private:
  std::map<TBcid, std::string> mapping_CID_NAME;
  std::map<TBcid, mod_info> mapping_CID_INFO;
  std::map<TString, TBcid> mapping_NAME_CID;

};

#endif
