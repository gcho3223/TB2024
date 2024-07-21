#include "TButility.h"

#include <iostream>
#include <stdexcept>
#include <fstream>

void TButility::LoadMapping(const std::string &path)
{

  int mid = 0;
	int ch = 0;
	TString* name = nullptr;
	int cases = 0;
	int isCeren = 0;
	int row = 0;
	int column = 0;

  std::cout << "Loading mapping file : " << path << std::endl;

  TChain *mapChain = new TChain("mapping");
  mapChain->Add((TString)path);

  mapChain->SetBranchAddress("mid", &mid);
  mapChain->SetBranchAddress("ch", &ch);
  mapChain->SetBranchAddress("cases", &cases);
  mapChain->SetBranchAddress("name", &name);
  mapChain->SetBranchAddress("isCeren", &isCeren);
  mapChain->SetBranchAddress("row", &row);
  mapChain->SetBranchAddress("column", &column);

  for (int i = 0; i < mapChain->GetEntries(); i++) {
    mapChain->GetEntry(i);

    if (*name == "null")
      continue;

    TBcid aCID = TBcid(mid, ch);
    mapping_CID_NAME.insert(std::make_pair(aCID, *name));
    mapping_CID_INFO.insert(std::make_pair(aCID, mod_info(cases, isCeren, row, column)));
    mapping_NAME_CID.insert(std::make_pair(*name, aCID));
  }

  // for (auto aMap : mapping_CID_NAME)
  //   std::cout << aMap.first.mid() << " " << aMap.first.channel() << " " << aMap.second << std::endl;

  // for (auto aMap : mapping_NAME_CID)
  //   std::cout << aMap.first << " " << aMap.second.mid() << " " << aMap.second.channel() << std::endl;

  delete mapChain;
}

TBcid TButility::GetCID(TString name) const {
  if (mapping_NAME_CID.find(name) == mapping_NAME_CID.end()) return TBcid(-1, -1);
  else return mapping_NAME_CID.at(name);
}

std::string TButility::GetName(TBcid cid) const {
  if (mapping_CID_NAME.find(cid) == mapping_CID_NAME.end()) return "null";
  else return mapping_CID_NAME.at(cid);
}

TButility::mod_info TButility::GetInfo(TBcid cid) const {
  if (mapping_CID_INFO.find(cid) == mapping_CID_INFO.end()) return mod_info(-1, -1, -1, -1);
  else return mapping_CID_INFO.at(cid);
}

TButility::mod_info TButility::GetInfo(TString name) const {
  TBcid aCID = GetCID(name);
  if (aCID == TBcid(-1, -1))
    return mod_info(-1, -1, -1, -1);

  return GetInfo(aCID);
}
