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
  mapChain->SetBranchAddress("nChannel", &nChannel);
  mapChain->SetBranchAddress("isCeren", &isCeren);
  mapChain->SetBranchAddress("row", &row);
  mapChain->SetBranchAddress("column", &column);

  for (int i = 0; i < mapChain->GetEntries(); i++)
  {
    mapChain->GetEntry(i);

    auto cid = TBcid(mid, ch);

    // if ( module==3 ) {
    //   TBdetector::detid adetid = this->detid(tower);
    //   auto det = TBdetector(adetid);

    //   // column starts from 0 for all auxiliary detectors
    //   int col = tower - static_cast<int>(adetid);
    //   det.encodeColumn(col);

    //   mapping_.insert(std::make_pair(cid,det));

    //   continue;
    // }

    if (cases == 0)
    {
      TBdetector det = TBdetector(TBdetector::detid::nulldet);
      mapping_.insert(std::make_pair(cid, det));

      continue;
    }

    if (cases == 13 || cases == 14)
    {
      TBdetector det;
      if (cases == 13)
        det = TBdetector(TBdetector::detid::MCPPMT);
      if (cases == 14)
        det = TBdetector(TBdetector::detid::SiPM);

      det.encodeModule(cases, nChannel, static_cast<bool>(isCeren));
      det.encodeMultiCh(row, column);

      mapping_.insert(std::make_pair(cid, det));

      continue;
    }

    TBdetector det;
    if (cases == 10)
      det = TBdetector(TBdetector::detid::SFHS);
    if (cases == 11)
      det = TBdetector(TBdetector::detid::LEGO);
    if (cases == 12)
      det = TBdetector(TBdetector::detid::MCPPMT_gen);

    if (cases == 4)
      det = TBdetector(TBdetector::detid::ext);
    if (cases == 6)
      det = TBdetector(TBdetector::detid::ceren);

    det.encodeModule(cases, nChannel, static_cast<bool>(isCeren));

    mapping_.insert(std::make_pair(cid, det));
  }

  delete mapChain;
}

TBcid TButility::GetCID(TString name) const {
  if (mapping_NAME_CID.find(name) == mapping_NAME_CID.end()) return TBcid(-1, -1);
  else return mapping_NAME_CID.at(name);
}

TString TButility::GetName(TBcid cid) const {
  if (mapping_CID_NAME.find(cid) == mapping_CID_NAME.end()) return "null";
  else return mapping_CID_NAME.at(cid);
}

mod_info TButility::GetInfo(TBcid cid) const {
  if (mapping_CID_INFO.find(cid) == mapping_CID_INFO.end()) return mod_info(-1, -1, -1, -1);
  else return mapping_CID_INFO.at(cid);
}

mod_info TButility::GetInfo(TString name) const {
  TBcid aCID = GetCID(name);
  if (aCID == TBcid(-1, -1))
    return mod_info(-1, -1, -1, -1);

  return GetInfo(aCID);
}
