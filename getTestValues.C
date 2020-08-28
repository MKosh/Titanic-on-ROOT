{
    // Get the average age value. Plot the age distrubtion for all known values (age>0)
    // and then pull the average from the plot, close the plot, and write the value to values.txt

    #include <fstream>
    
    // Load in the root file we just made
    TFile *f = new TFile("train.root");

    Double_t aveAge;
    Testing->Draw("Age", "Age>0");
    aveAge = htemp->GetMean();
    c1->Close();

    cout << aveAge << endl;

    f->Close();

    std::ofstream ofs ("values.txt", std::ofstream::out);
    ofs << "age," << aveAge << std::endl;
    ofs.close()

}