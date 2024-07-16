


int sample() {


  TH1D* test = new TH1D("", "", 10, 0., 10.);

  test->Fill(5, 10);

  TCanvas* c = new TCanvas("", "");
  c->cd();
  test->Draw("Hist");

  int i = 1;
  while(i++) {
    std::cout << i << std::endl;
    gSystem->Sleep(10000);
    if (i >= 10) i = i - 10;

    test->Fill(i, 3);
    c->cd();
    test->Draw();
  }


  return 1;
}
