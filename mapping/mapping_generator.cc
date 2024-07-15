#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TTree.h"


int mapping_generator(std::string inputMap) {

	int mid = 0;
	int ch = 0;
	TString name = "";
	int cases = 0;
	int isCeren = 0;
	int row = 0;
	int column = 0;

	TTree* aTree = new TTree("mapping", "mapping");

	aTree->Branch("mid", &mid);
	aTree->Branch("ch", &ch);
	aTree->Branch("name", &name);
	aTree->Branch("cases", &cases);
	aTree->Branch("isCeren", &isCeren);
	aTree->Branch("row", &row);
	aTree->Branch("column", &column);

  std::ifstream in;
  in.open(inputMap + ".csv", std::ios::in);
  while (true) {
    in >> mid >> ch >> name >> cases >> isCeren >> row >> column;
    if (!in.good()) break;
    aTree->Fill();
  }
  in.close();


  TFile* aFile = new TFile((TString)(inputMap + ".root"), "RECREATE");
  aTree->Write();
  aFile->Close();



  return 1;
}