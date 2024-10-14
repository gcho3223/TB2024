/*

// -- HistSet: easily control many histograms
HistSet *histSet = new HistSet("type"); // -- or put ""
histSet->Register("pt",  10000, 0,   10000); // -- it will make "h_pt" histogram with given bin info
histSet->Register("eta", 200,   -10, 10); // -- it will make "h_eta" histogram with given bin info
...
// -- end of register -- //

// -- fill part
for(auto& mu : vec_muon ) {
  ...
  histSet-->Fill( "pt", mu.pt, eventWeight );
  histSet-->Fill( "eta", mu.pt, eventWeight )

  // -- you can add additional "tag": it will automatically creates "pt_leading" histogram
  histSet-->Fill( "pt", "leading", mu.pt, eventWeight );;
  ...
}

// -- save part
histSet->Write();

*/

#include <TString.h>
#include <TH1D.h>

#include <utility>
#include <map>
#include <iostream>

class HistSet { 
public:
  HistSet(TString type) { type_ = type; }

  void Register(TString var, Int_t nBin, Double_t min, Double_t max) {

    TString histName = "h_"+var+"_"+type_;
    if( type_ == "" )
      histName = "h_"+var;

    TH1D* h_temp = new TH1D(histName, "", nBin, min, max);

    map_var_hist_.insert( std::make_pair(var, h_temp) );
  }

  void Fill(TString var, Double_t value, Double_t weight = 1.0 ) {

    auto it_pair = map_var_hist_.find(var);
    if( it_pair == map_var_hist_.end() )
      std::cout << "no histogram corresponding to " << var << std::endl;
    else
      it_pair->second->Fill( value, weight );
  }

  // -- when you fill the histogram with a tag
  // -- if no histogram was registered with the tag, it will automatically add the new histogram with the given tag
  void Fill(TString baseVar, TString tag, Double_t value, Double_t weight = 1.0 ) {
    if( tag == "" ) { // -- no tag case
      Fill(baseVar, value, weight);
      return;
    }

    TString var_wTag = TString::Format("%s_%s", baseVar.Data(), tag.Data());

    auto it_pair = map_var_hist_.find(var_wTag);
    if( it_pair == map_var_hist_.end() ) {
      // -- if no histogram is available with the tag, make it:
      std::cout << "no "+baseVar+" histogram is registered for the tag = " + tag + " ... make it" << std::endl;
      TH1D* h_baseVar = Get(baseVar);

      TH1D* h_var_wTag = (TH1D*)h_baseVar->Clone();
      h_var_wTag->Reset("ICES"); // -- should be reset...

      TString histName = h_baseVar->GetName();
      histName.ReplaceAll(baseVar, var_wTag);
      h_var_wTag->SetName(histName);

      h_var_wTag->Fill( value, weight );

      map_var_hist_.insert( std::make_pair(var_wTag, h_var_wTag) );
    }
    else
      it_pair->second->Fill( value, weight );
  }

  void Write() {
    for(auto pair : map_var_hist_ )
      pair.second->Write();
  }

  TH1D* Get(TString var) {
    auto it_pair = map_var_hist_.find(var);
    if( it_pair == map_var_hist_.end() )
      std::cout << "[HistSet::Get] no histogram corresponding to " << var << std::endl;
    else
      return it_pair->second;

    return nullptr;
  }

private:
  TString type_;
  std::map<TString, TH1D*> map_var_hist_;
};