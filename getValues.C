{
    // Load in the root file we just made
    TFile *f = new TFile("train.root");

    Double_t aveAge;
    Training->Draw("Age", "Age>0");
    aveAge = htemp->GetMean();
    c1->Close();
    cout << aveAge << endl;
    
    f->Close();
}