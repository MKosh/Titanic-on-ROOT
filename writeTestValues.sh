#!/bin/bash

# Write the average age into the empty age leaves
inFile="values.txt"
trainFile="./data/testing.csv"
aveAge=$( cat $inFile | grep ^a | awk -F',' '{print $2}' )

sed -i 's/-1/'$aveAge'/g' $trainFile # Replace -1 values with the average age

echo "Done!"