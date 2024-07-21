#include "TBplotengine.h"
#include "TSystem.h"

TBplotengine::TBplotengine(const YAML::Node fConfig_, int fRunNum_, TButility fUtility_)
: fConfig(fConfig_), fRunNum(fRunNum_), fUtility(fUtility_), fCaseName("")
{}

void TBplotengine::init()
{
  fUtility.LoadMapping("../mapping/mapping_TB2024_v1.root");

  if (fCaseName == "single") {
   for (int i = 0; i < fCIDtoPlot.size(); i++) {
      TBcid aCID = fCIDtoPlot.at(i);
      std::string aName =fUtility.GetName(aCID);
      TButility::mod_info aInfo = fUtility.GetInfo(aCID);

      if (fCalcInfo == TBplotengine::CalcInfo::kIntADC ||fCalcInfo == TBplotengine::CalcInfo::kPeakADC) {
        std::vector<int> interval = fConfig[aName].as<std::vector<int>>();
        fPlotter.push_back(TBplotengine::PlotInfo(aCID, aName, aInfo, interval.at(0), interval.at(1)));

        if (fCalcInfo == TBplotengine::CalcInfo::kIntADC)
          fPlotter.at(i).SetPlot(new TH1D((TString)(aName), ";nBin;IntADC", 220, -3000., 30000.));

        if (fCalcInfo == TBplotengine::CalcInfo::kPeakADC)
          fPlotter.at(i).SetPlot(new TH1D((TString)(aName), ";nBin;PeakADC", 256, 0., 4096.));

      } else {
        fPlotter.push_back(TBplotengine::PlotInfo(aCID, aName, aInfo));
      }
    }

    int argc = 0;
    char* argv[] = {};
    fApp = new TApplication("app", &argc, argv);
    fApp->SetReturnFromRun(true);
    fCanvas = new TCanvas("", "");

    Draw();

    for (int i = 0; i < fPlotter.size(); i++)
      std::cout << fPlotter.at(i).hist1D->GetName() << std::endl;
  }



  // PrintInfo();
}

double TBplotengine::GetPeakADC(std::vector<short> waveform, int xInit, int xFin) {

  // std::cout << "GetPeakADC" << " " << xInit << " " << xFin << std::endl;

  double ped = 0;
  for (int i = 1; i < 101; i++)
    ped += (double)waveform.at(i) / 100.;

  std::vector<double> pedCorWave;
  for (int i = xInit; i < xFin; i++)
    pedCorWave.push_back(ped - (double)waveform.at(i));

  return *std::max_element(pedCorWave.begin(), pedCorWave.end());
}

double TBplotengine::GetIntADC(std::vector<short> waveform, int xInit, int xFin) {

  // std::cout << "GetIntADC" << " " << xInit << " " << xFin << " " << waveform.size() << std::endl;

  double ped = 0;
  for (int i = 1; i < 101; i++)
    ped += (double)waveform.at(i) / 100.;

  double intADC_ = 0;
  for (int i = xInit; i < xFin; i++)
    intADC_ += ped - (double)waveform.at(i);

  return intADC_;
}


void TBplotengine::PrintInfo() {

}

void TBplotengine::Fill(TBevt<TBwaveform> anEvent) {

  // std::cout << "Starting Fill" << std::endl;

  for (int i = 0; i < fPlotter.size(); i++) {
    if (fCaseName == "single") {
      double value = GetValue(anEvent.GetData(fPlotter.at(i).cid).waveform(), fPlotter.at(i).xInit, fPlotter.at(i).xFin);
      // std::cout << fPlotter.at(i).hist1D->GetName() << " " << value << std::endl;

      fPlotter.at(i).hist1D->Fill(value);
    }
  }
}

void TBplotengine::Draw() {

  fCanvas->cd();
  if (fCaseName == "single") {
    for (int i = 0; i < fPlotter.size(); i++) {
      std::cout << fPlotter.at(i).hist1D->GetName() << " " <<
                   fPlotter.at(i).hist1D->GetEntries() <<  " " <<
                   fPlotter.at(i).hist1D->GetMean() << std::endl;

      if (i == 0) fPlotter.at(i).hist1D->Draw("Hist");
      else        fPlotter.at(i).hist1D->Draw("Hist & same");

    }
  }
  gSystem->ProcessEvents();
  gSystem->Sleep(3000);

}

void TBplotengine::Update() {

  fCanvas->Update();
  fCanvas->Pad()->Draw();
  gSystem->ProcessEvents();
}

void TBplotengine::SaveAs(TString output)
{
  // output = (TString)("./ROOT/"+ output);
  // if (fCaseName != "")
  //   output = (TString)(output + "_" + fCaseName);

  // TFile *outoutFile = new TFile(output + ".root", "RECREATE");

  // outoutFile->cd();
  // for (int i = 0; i < fCIDtoPlot.size(); i++)
  //   for (int j = 0; j < fPlotSet.at(fCIDtoPlot.at(i)).size(); j++)
  //     fPlotSet.at(fCIDtoPlot.at(i)).at(j).second->GetHisto()->Write();

  // outoutFile->Close();
}
