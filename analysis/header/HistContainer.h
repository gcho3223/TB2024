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

    Fill_DRC(anEvt, theDRC);

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

  void Init() {
    histSet_ = new HistSet(tag_);
    histSet_->Register("intADC",  320, -20000, 300000);
    histSet_->Register("peakADC", 4096, 0, 4096);
    // histSet_->Register("eDep", 440, -20, 200); // -- in GeV
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

  void Fill_DRC(TBevt<TBwaveform>* anEvt, DRC& theDRC, double weight = 1.0) {
    for(int i_mo=0; i_mo<theDRC.nModule(); ++i_mo) {
      int moduleNum = i_mo+1;
      DRCModule& module = theDRC.Get_Module(moduleNum);

      for(int i_tower=0; i_tower<module.nTower(); ++i_tower) {
        int towerNum = i_tower+1;
        DRCTower& tower = module.Get_Tower(towerNum);
        DRCFiber& fiber_c = tower.Get_Fiber("c");
        DRCFiber& fiber_s = tower.Get_Fiber("s");

        histSet_->Fill("intADC", fiber_c.Tag(), fiber_c.Get_IntADC(anEvt), weight);
        histSet_->Fill("intADC", fiber_s.Tag(), fiber_s.Get_IntADC(anEvt), weight);
      } // -- iter over. towers
    } // -- iter over. modules
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