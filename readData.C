{
    // Read the data that the cleanForRoot.sh file generated

    // Make a new file called train.root, overwrite any old ones
    TFile *f = new TFile("train.root");

    // Make a new tree in the file called Training
    TTree *tree = new TTree("Training", "Training Data");

    // Load the data from ./data/train.csv into the tree
    tree->ReadFile("data/training.csv","PassengerId/I:Survived/I:Pclass/I:Name/C:Sex/I:Age/F:SibSp/I:Parch/I:Ticket/C:Fare/F:Section/C:Room/I:Embarked/C",',');
    
    // Write the files, and close/delete everything from memory
    f->Write();
    f->Close();
    //delete f;
    //delete tree;

    //cout << "Done!" << endl;
}
