#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

using namespace TMVA;

void RegressionApp( TString myMethodList = "" )
{
    TMVA::Tools::Instance();

    TFile *input = TFile::Open("test.root");
    TFile *outFile = new TFile("RegressionOutput.root", "RECREATE");
   // std::map<std::string,int> Use;

    // Use["LD"] = 1;
    //Use["BDTG"] = 1;

    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
    Float_t Sex, Age, SibSp, Parch, Fare, Survived;
    reader->AddVariable( "Sex", &Sex );
    reader->AddVariable( "Age", &Age );
    reader->AddVariable( "SibSp", &SibSp );
    reader->AddVariable( "Parch", &Parch );
    reader->AddVariable( "Fare", &Fare );

    reader->BookMVA( "BDTG_HU", "dataset/weights/TMVARegression_BDTG_HU.weights.xml");
    reader->BookMVA( "BDTG_LS", "dataset/weights/TMVARegression_BDTG_LS.weights.xml");

    TTree* theTree = (TTree*)input->Get("Testing");
    TTree* outTree = new TTree("Results", "Predicted Survival");
    TBranch *bran = outTree->Branch("Survived",&Survived,"Survived/I");
    //TBranch *b = theTree->Branch("Survived",&Survived);
    
    for (Long64_t ievt=0; ievt<theTree->GetEntries(); ievt++) {
        
        if (ievt%100 == 0) {
            std::cout << " Processing event: " << ievt << std::endl;
        }

        theTree->GetEntry(ievt);
        Survived = reader->EvaluateMVA( "BDTG_HU" );
        outTree->Fill();

    }

    outFile->Write();
    outFile->Close();
    delete reader;

    std::cout << " Regression Complete! Look for file RegressionOutput.root" << std::endl;
}