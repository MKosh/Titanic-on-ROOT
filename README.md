# Titanic-on-ROOT
## Analyzing the Titanic dataset with ROOT

This is a work in progress side project to learn the TMVA framework in ROOT using a dataset that has a lot of resources online.

### How to do the analysis
* First run

  `./cleanForRoot.sh`
  
This cleans the training data in "train.csv" and outputs a file "training.csv". Missing data gets filled in with placeholder values, and the "," in the Name field is replaced by "--". This lets you load the data into ROOT, without these ROOT gets confused and just gives a bunch of errors. For now missing ages are set to -1, and any missing string value is set to "EMPTY".

* Next start a root session and then at the prompt

  `.x readData.C`
  
That creates the "train.root" file and the TTree "Training" inside of it.
