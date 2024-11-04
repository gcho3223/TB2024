#include "TBread.h"
#include "TButility.h"

#include "HistSet.h"
#include "detector/AuxDetector.h"
#include "detector/DWCPair.h"
#include "detector/DRC.h"

class HistContainer {
public:
  HistContainer(TString tag): tag_(tag) { Init(); }

  void Fill(TBevt<TBwaveform>* anEvt, DRC& theDRC, DWCPair& theDWCPair, AuxDetector& thePS, AuxDetector& theMC, double weight = 1.0) {
    nEvent_ += weight;

    Fill_DRC(theDRC);

    Fill_DWC(anEvt, theDWCPair);
    histSet_->Fill("peakADC", thePS.Tag(), thePS.Get_PeakADC(anEvt), weight);
    histSet_->Fill("peakADC", theMC.Tag(), theMC.Get_PeakADC(anEvt), weight);
  }

  void Write() {
    histSet_->Write();
    for(auto& h2D : vec_hist2D_ )
      h2D->Write();

    // -- save # events as a histogram
    TString histName = (tag_ == "") ? "h_nEvent" : "h_nEvent_"+tag_;
    TH1D* h_nEvent = new TH1D(histName, "", 1, 0, 1);
    h_nEvent->SetBinContent(1, nEvent_);
    h_nEvent->SetBinError(1, 0);
    h_nEvent->Write();
  }

private:
  TString tag_;

  int nEvent_ = 0; // -- keep # processed events
  HistSet *histSet_;

  // -- additional 2D histograms (a few)
  std::vector<TH2D*> vec_hist2D_;
  TH2D* h2D_pos_DWC1_;
  TH2D* h2D_pos_DWC2_;
  TH2D* h2D_posCorrel_x_;
  TH2D* h2D_posCorrel_y_;

  // -- for patial energy sum
  // -- module & towerNum near M8T2
  std::map<int, std::vector<int>> map_towerNum_nearM8T2_ = {
    {5, {3, 4} }, // -- module 5, tower 3 and 4
    {6, {3} },
    {8, {1, 2, 3, 4} },
    {9, {1, 3} },
  };

  void Init() {
    histSet_ = new HistSet(tag_);
    histSet_->Register("intADC",  320, -20000, 300000);
    histSet_->Register("peakADC", 4096, 0, 4096);
    histSet_->Register("eDep", 640, -20, 300); // -- in GeV
    histSet_->Register("posDiffDWC", 200, 0, 100);

    h2D_pos_DWC1_ = new TH2D("h2D_pos_DWC1",       "", 480, -120., 120., 480, -120., 120.); vec_hist2D_.push_back(h2D_pos_DWC1_);
    h2D_pos_DWC2_ = new TH2D("h2D_pos_DWC2",       "", 480, -120., 120., 480, -120., 120.); vec_hist2D_.push_back(h2D_pos_DWC2_);
    h2D_posCorrel_x_ = new TH2D("h2D_posCorrel_x", "", 480, -120., 120., 480, -120., 120.); vec_hist2D_.push_back(h2D_posCorrel_x_);
    h2D_posCorrel_y_ = new TH2D("h2D_posCorrel_y", "", 480, -120., 120., 480, -120., 120.); vec_hist2D_.push_back(h2D_posCorrel_y_);
    for(auto& h2D : vec_hist2D_ ) {
      if( tag_ != "" ) {
        TString histName_new = h2D->GetName();
        histName_new += "_"+tag_;
        h2D->SetName(histName_new);
      }
    }
  }

  void Fill_DRC(DRC& theDRC, double weight = 1.0) {
    for(int i_mo=0; i_mo<theDRC.nModule(); ++i_mo) {
      int moduleNum = i_mo+1;
      DRCModule& module = theDRC.Get_Module(moduleNum);

      for(int i_tower=0; i_tower<module.nTower(); ++i_tower) {
        int towerNum = i_tower+1;
        DRCTower& tower = module.Get_Tower(towerNum);
        DRCFiber& fiber_c = tower.Get_Fiber("c");
        DRCFiber& fiber_s = tower.Get_Fiber("s");

        histSet_->Fill("intADC", fiber_c.Tag(), fiber_c.Get_IntADC(), weight);
        histSet_->Fill("intADC", fiber_s.Tag(), fiber_s.Get_IntADC(), weight);

        histSet_->Fill("eDep", "noSF_"+fiber_c.Tag(), fiber_c.Get_Energy(kFALSE), weight);
        histSet_->Fill("eDep", "noSF_"+fiber_s.Tag(), fiber_s.Get_Energy(kFALSE), weight);  
        histSet_->Fill("eDep",         fiber_c.Tag(), fiber_c.Get_Energy(kTRUE),  weight);
        histSet_->Fill("eDep",         fiber_s.Tag(), fiber_s.Get_Energy(kTRUE),  weight);

        histSet_->Fill("eDep", "noSF_"+tower.Tag(),   tower.Get_EnergySum("all", kFALSE), weight);
        histSet_->Fill("eDep",         tower.Tag(),   tower.Get_EnergySum("all", kTRUE),  weight);
      } // -- iter over. towers

      histSet_->Fill("eDep", "noSF_"+module.Tag()+"-C", module.Get_EnergySum("c", kFALSE), weight);
      histSet_->Fill("eDep",         module.Tag()+"-C", module.Get_EnergySum("c", kTRUE),  weight);
      histSet_->Fill("eDep", "noSF_"+module.Tag()+"-S", module.Get_EnergySum("s", kFALSE), weight);
      histSet_->Fill("eDep",         module.Tag()+"-S", module.Get_EnergySum("s", kTRUE),  weight);

      histSet_->Fill("eDep", "noSF_"+module.Tag(), module.Get_EnergySum("all", kFALSE), weight);
      histSet_->Fill("eDep",         module.Tag(), module.Get_EnergySum("all", kTRUE),  weight);
    } // -- iter over. modules

    histSet_->Fill("eDep", "noSF_all-C", theDRC.Get_EnergySum("c", kFALSE), weight);
    histSet_->Fill("eDep", "all-C",      theDRC.Get_EnergySum("c", kTRUE),  weight);
    histSet_->Fill("eDep", "noSF_all-S", theDRC.Get_EnergySum("s", kFALSE), weight);
    histSet_->Fill("eDep", "all-S",      theDRC.Get_EnergySum("s", kTRUE),  weight);

    histSet_->Fill("eDep", "noSF_all", theDRC.Get_EnergySum("all", kFALSE), weight);
    histSet_->Fill("eDep", "all",      theDRC.Get_EnergySum("all", kTRUE),  weight);

    // -- partial energy sum
    // -- near M8T2
    histSet_->Fill("eDep", "noSF_nearM8T2-C", theDRC.Get_PartialEnergySum(map_towerNum_nearM8T2_, "c",   kFALSE), weight);
    histSet_->Fill("eDep", "nearM8T2-C",      theDRC.Get_PartialEnergySum(map_towerNum_nearM8T2_, "c",   kTRUE),  weight);
    histSet_->Fill("eDep", "noSF_nearM8T2-S", theDRC.Get_PartialEnergySum(map_towerNum_nearM8T2_, "s",   kFALSE), weight);
    histSet_->Fill("eDep", "nearM8T2-S",      theDRC.Get_PartialEnergySum(map_towerNum_nearM8T2_, "s",   kTRUE),  weight);
    histSet_->Fill("eDep", "noSF_nearM8T2",   theDRC.Get_PartialEnergySum(map_towerNum_nearM8T2_, "all", kFALSE), weight);
    histSet_->Fill("eDep", "nearM8T2",        theDRC.Get_PartialEnergySum(map_towerNum_nearM8T2_, "all", kTRUE),  weight);
  }

  void Fill_DWC(TBevt<TBwaveform>* anEvt, DWCPair& theDWCPair, double weight = 1.0) {
    std::vector<float> vec_pos_DWC1 = theDWCPair.Get_DWC1().GetPosition_Corr(anEvt);
    h2D_pos_DWC1_->Fill( vec_pos_DWC1[0], vec_pos_DWC1[1], weight);

    std::vector<float> vec_pos_DWC2 = theDWCPair.Get_DWC2().GetPosition_Corr(anEvt);
    h2D_pos_DWC2_->Fill( vec_pos_DWC2[0], vec_pos_DWC2[1], weight);

    h2D_posCorrel_x_->Fill( vec_pos_DWC1[0], vec_pos_DWC2[0], weight );
    h2D_posCorrel_y_->Fill( vec_pos_DWC1[1], vec_pos_DWC2[1], weight );

    std::vector<float> vec_posDiff = theDWCPair.Get_PosDiff(vec_pos_DWC1, vec_pos_DWC2);
    histSet_->Fill("posDiffDWC", "x", vec_posDiff[0], weight);
    histSet_->Fill("posDiffDWC", "y", vec_posDiff[1], weight);
  }
};