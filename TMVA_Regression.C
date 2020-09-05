{
TMVA::Tools::Instance();

auto inputFile = TFile::Open("train.root");

auto outputFile = TFile::Open("TMVA_RegressionOutput.root", "RECREATE");

TMVA::Factory factory("TMVARegression", outputFile, "!V:!Silent:Color:!DrawProgressBar:AnalysisType=Regression" );

TMVA::DataLoader loader("dataset");

loader.AddVariable("Sex");
loader.AddVariable("Age");
loader.AddVariable("SibSp");
loader.AddVariable("Parch");
loader.AddVariable("Fare");

loader.AddTarget( "Survived" );

TTree* tree = (TTree*)inputFile->Get("Training");

TCut mycuts = "";

loader.AddRegressionTree(tree, 1.0);
loader.PrepareTrainingAndTestTree(mycuts, "nTrain_Regression=0:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V" );

factory.BookMethod(&loader,TMVA::Types::kBDT, "BDTG_HU", TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+TString("RegressionLossFunctionBDTG=Huber"));
factory.BookMethod(&loader,TMVA::Types::kBDT, "BDTG_LS", TString("!H:!V:NTrees=64::BoostType=Grad:Shrinkage=0.3:nCuts=20:MaxDepth=4:")+TString("RegressionLossFunctionBDTG=LeastSquares"));

factory.TrainAllMethods();

factory.TestAllMethods();

factory.EvaluateAllMethods();

outputFile->Close();
auto resultsFile = TFile::Open("TMVA_RegressionOutput.root");
auto resultsTree = (TTree*) resultsFile->Get("dataset/TestTree");

auto h1 = new TH1D("h1","BDTG-target", 100, 1,0);
resultsTree->Draw("BDTG_HU-target >> h1");
auto h2 = (TH1*) h1->Clone("h2");
resultsTree->Draw("BDTG_LS-target >> h2");
h1->SetLineColor(kBlue);
h1->Draw();
h2->SetLineColor(kRed);
h2->Draw("SAME");
gPad->Draw();

}
