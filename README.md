# Titanic-on-ROOT
## Analyzing the Titanic dataset with ROOT

This is a work in progress side project to learn the TMVA framework in ROOT using a dataset that has a lot of resources online. Tested on Ubuntu 20.04 running under Windows 10 WSL2.

## Known issues

There are issues when going between linux file types and windows. The first two lines are where the most errors come up. It's suggested that you first convert the train.csv file type to the correct format if you download it directly from somewhere like Kaggle. Open the file in VS Code and set the End of Line sequence at the bottom right to LF instead of CRLF and save it.

### How to do the analysis
* First run

  `./cleanForRoot.sh`
  
This cleans the training data in "train.csv" and outputs a file "training.csv". Missing data gets filled in with placeholder values, and the "," in the Name field is replaced by "--". This lets you load the data into ROOT, without these ROOT gets confused and just gives a bunch of errors. For now missing ages are set to -1, and any missing string value is set to "EMPTY".

* Next start a root session and then at the prompt

  `.x readData.C`
  
That creates the "train.root" file and the TTree "Training" inside of it. Analysis can be started here, or you can add in the mean age to all of the missing values.

* In a ROOT terminal

  `.x getValues.C`
  
* Back in bash run

  `./writeValues.sh`
  
This macro and script can be updated to fill in any missing data you want.

* Back in ROOT, run one last

  `.x readData.C`
  
