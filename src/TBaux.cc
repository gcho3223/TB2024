#include "TBaux.h"
#include "GuiTypes.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TPaveStats.h"


TBaux::TBaux(const YAML::Node fNodePlot_, int fRunNum_, bool fPlotting_, bool fLive_, TButility fUtility_)
: fNodeAux(fNodePlot_), fRunNum(fRunNum_), fPlotting(fPlotting_), fLive(fLive_), fUtility(fUtility_)
{

  fDWCCalib = fNodeAux["DWC"]["CALIB"].as<std::vector<double>>();
  fDWCCenter = fNodeAux["DWC"]["CENTER"].as<std::vector<double>>();
}

void TBaux::init() {

  // int argc = 0;
  // char* argv[] = {};
  // fApp = new TApplication("fApp_AUX", &argc, argv);
  // if (fLive)
  //   fApp->SetReturnFromRun(true);


  fCIDtoPlot.push_back(fUtility.GetCID("CC1"));
  fCIDtoPlot.push_back(fUtility.GetCID("CC2"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC1R"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC1L"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC1U"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC1D"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC2R"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC2L"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC2U"));
  fCIDtoPlot.push_back(fUtility.GetCID("DWC2D"));
  fCIDtoPlot.push_back(fUtility.GetCID("PS"));
  fCIDtoPlot.push_back(fUtility.GetCID("MC"));

  fPScut = fNodeAux["PS"][fMethod].as<double>();
  fMCcut = fNodeAux["MC"][fMethod].as<double>();
  fCC1cut = fNodeAux["CC1"][fMethod].as<double>();
  fCC2cut = fNodeAux["CC2"][fMethod].as<double>();

  fDWC1 = new TH2D("DWC1", "DWC 1 position;X [mm];Y [mm]", 200, -50., 50., 200, -50., 50.);
  fDWC1->SetStats(0);

  fDWC2 = new TH2D("DWC2", "DWC 2 position;X [mm];Y [mm]", 200, -50., 50., 200, -50., 50.);
  fDWC2->SetStats(0);

  fDWCXaxis = new TH2D("DWC_X", "DWC X corr;DWC 1 X [mm];DWC 2 X [mm]", 200, -50., 50., 200, -50., 50.);
  fDWCXaxis->SetStats(0);

  fDWCYaxis = new TH2D("DWC_Y", "DWC Y corr;DWC 1 Y [mm];DWC 2 Y [mm]", 200, -50., 50., 200, -50., 50.);
  fDWCYaxis->SetStats(0);

  if (fMethod == "IntADC") {
    fPS = new TH1D("PS", "PS - IntADC;IntADC;nEvents", 440, -30000., 300000.);
    fMC = new TH1D("MC", "MC - IntADC;IntADC;nEvents", 440, -30000., 300000.);
  } else if (fMethod == "PeakADC") {
    fPS = new TH1D("PS", "PS - PeakADC;PeakADC;nEvents", 288, -512., 4096.);
    fMC = new TH1D("MC", "MC - PeakADC;PeakADC;nEvents", 288, -512., 4096.);
  }

  fPS->SetLineColor(4);
  fPS->SetLineWidth(2);

  fMC->SetLineColor(2);
  fMC->SetLineWidth(2);

  fCanvas = new TCanvas("fCanvas_Aux", "fCanvas_Aux", 1900, 1000);
  fCanvas->Divide(3, 2);

  fCanvas->cd(1)->SetRightMargin(0.13);
  fCanvas->cd(2)->SetRightMargin(0.13);
  fCanvas->cd(3)->SetRightMargin(0.13);
  fCanvas->cd(5)->SetRightMargin(0.13);

}

void TBaux::SetRange(const YAML::Node tConfigNode) {

  fRangeMap.insert(std::make_pair("PS", tConfigNode["PS"].as<std::vector<int>>()));
  fRangeMap.insert(std::make_pair("MC", tConfigNode["MC"].as<std::vector<int>>()));
  fRangeMap.insert(std::make_pair("CC1", tConfigNode["CC1"].as<std::vector<int>>()));
  fRangeMap.insert(std::make_pair("CC2", tConfigNode["CC2"].as<std::vector<int>>()));
}

double TBaux::GetPeakADC(std::vector<short> waveform, int xInit, int xFin) {
  double ped = 0;
  for (int i = 1; i < 101; i++)
    ped += (double)waveform.at(i) / 100.;

  std::vector<double> pedCorWave;
  for (int i = xInit; i < xFin; i++)
    pedCorWave.push_back(ped - (double)waveform.at(i));

  return *std::max_element(pedCorWave.begin(), pedCorWave.end());
}

double TBaux::GetIntADC(std::vector<short> waveform, int xInit, int xFin) {
  double ped = 0;
  for (int i = 1; i < 101; i++)
    ped += (double)waveform.at(i) / 100.;

  double intADC_ = 0;
  for (int i = xInit; i < xFin; i++)
    intADC_ += ped - (double)waveform.at(i);

  return intADC_;
}

void TBaux::Fill(TBevt<TBwaveform> anEvent) {

  fDWC1->Fill(0., 0.);
  fDWC2->Fill(0., 0.);
  fDWCXaxis->Fill(0., 0.);
  fDWCYaxis->Fill(0., 0.);

  fPS->Fill(GetValue(anEvent.GetData(fUtility.GetCID("PS")).waveform(), fRangeMap.at("PS").at(0), fRangeMap.at("PS").at(1)));
  fMC->Fill(GetValue(anEvent.GetData(fUtility.GetCID("MC")).waveform(), fRangeMap.at("MC").at(0), fRangeMap.at("MC").at(1)));
}

void TBaux::Draw() {

  fCanvas->cd(1);
  fDWC1->Draw("colz");

  fCanvas->cd(4);
  fDWC2->Draw("colz");

  fCanvas->cd(2);
  fDWCXaxis->Draw("colz");

  fCanvas->cd(5);
  fDWCYaxis->Draw("colz");

  fCanvas->cd(3);
  fPS->Draw("colz");

  fCanvas->cd(6);
  fMC->Draw("colz");

  gSystem->ProcessEvents();
  gSystem->Sleep(3000);
}

void TBaux::Update() {

  fCanvas->cd(1);
  fDWC1->Draw("colz");

  fCanvas->cd(4);
  fDWC2->Draw("colz");

  fCanvas->cd(2);
  fDWCXaxis->Draw("colz");

  fCanvas->cd(5);
  fDWCYaxis->Draw("colz");

  fCanvas->cd(3);
  fPS->Draw("colz");

  fCanvas->cd(6);
  fMC->Draw("colz");

  // SaveAs("");
  fCanvas->Update();
  fCanvas->Pad()->Draw();

  if (!fLive) {
    fApp->Run(true);
  } else {
    gSystem->ProcessEvents();
  }

  gSystem->Sleep(5000);
}
