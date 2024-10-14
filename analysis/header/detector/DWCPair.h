#include "DWC.h"

class DWCPair {
public:
  DWCPair(TButility& util, TString tag1, TString tag2) { Init(util, tag1, tag2); }

  DWC& Get_DWC1() { return pair_DWC_.first; }
  DWC& Get_DWC2() { return pair_DWC_.second; }

  // -- when anEvt is provided
  std::vector<float> Get_PosDiff(TBevt<TBwaveform>* anEvt) {
    std::vector<float> pos_DWC1 = Get_DWC1().GetPosition_Corr(anEvt);
    std::vector<float> pos_DWC2 = Get_DWC2().GetPosition_Corr(anEvt);

    return Get_PosDiff(pos_DWC1, pos_DWC2);
  }

  // -- when you already have pos_DWC1 and pos_DWC2
  std::vector<float> Get_PosDiff(std::vector<float>& pos_DWC1,
                                 std::vector<float>& pos_DWC2 ) {
    float diff_x = std::abs(pos_DWC1.at(0) - pos_DWC2.at(0));
    float diff_y = std::abs(pos_DWC1.at(1) - pos_DWC2.at(1));
    return {diff_x, diff_y};
  }

  bool Pass(TBevt<TBwaveform>* anEvt) {
    std::vector<float> pos_DWC1 = Get_DWC1().GetPosition_Corr(anEvt);
    std::vector<float> pos_DWC2 = Get_DWC2().GetPosition_Corr(anEvt);

    if( !(TB2024::cut_DWC_size.first <= pos_DWC1[0] && pos_DWC1[0] <= TB2024::cut_DWC_size.second) ) return kFALSE;
    if( !(TB2024::cut_DWC_size.first <= pos_DWC1[1] && pos_DWC1[1] <= TB2024::cut_DWC_size.second) ) return kFALSE;
    if( !(TB2024::cut_DWC_size.first <= pos_DWC2[0] && pos_DWC2[0] <= TB2024::cut_DWC_size.second) ) return kFALSE;
    if( !(TB2024::cut_DWC_size.first <= pos_DWC2[1] && pos_DWC2[1] <= TB2024::cut_DWC_size.second) ) return kFALSE;

    std::vector<float> posDiff = Get_PosDiff(pos_DWC1, pos_DWC2);
    if( !(TB2024::cut_DWC_diff_x.first <= posDiff[0] && posDiff[0] <= TB2024::cut_DWC_diff_x.second) ) return kFALSE;
    if( !(TB2024::cut_DWC_diff_y.first <= posDiff[1] && posDiff[1] <= TB2024::cut_DWC_diff_y.second) ) return kFALSE;

    return kTRUE;
  }

private:
  std::pair<TString, TString> pair_tag_;
  std::pair<DWC, DWC> pair_DWC_;

  void Init(TButility& util, TString tag1, TString tag2) {
    pair_tag_ = std::pair<TString, TString>(tag1, tag2);
    pair_DWC_ = std::pair<DWC, DWC>( DWC(util, tag1), DWC(util, tag2) );
  }




};