#!/bin/bash
# Script for cleaning up the titanic dataset for ROOT

trainFile="./data/train.csv"
outFile="./data/training.csv"

cols_missing_data=()
cols=$( cat $trainFile | awk -F',' '{print NF; exit}' )
for (( i=1; i<=$cols; i++ )) # Loop over columns and count missing data
do
    count=$( cat $trainFile | awk -F',' '{print$'$i'}' | grep -cE ^$ )
    if [ $count -ne 0 ]
    then
#       $cols_missing_data+=( $i )
        echo "Missing values in col $i : $count"
    fi
done

sed -i 's/,\ /--\ /g' $trainFile # Remove ',' from the name column
cat $trainFile | awk -F',' '{print $1","$2","$3","$4}' > traintemp1.csv

for (( i=1; i<=$cols; i++ )) # Loop over the columns
do
    if [ $i -eq 5 ]
    then
        cat $trainFile | awk -F',' '{print $5}' | sed 's/female/1/g' | sed 's/male/0/g' | paste traintemp1.csv - -d',' > traintemp2.csv # Set females to value 1, males to 0
    elif [ $i -eq 6 ]
    then
        cat $trainFile | awk -F',' '{print $6}' | sed 's/^$/-1/g' | paste traintemp2.csv - -d',' > traintemp1.csv # Replace missing Age values with -1
        cat $trainFile | awk -F',' '{print $7","$8","$9","$10}' | paste traintemp1.csv - -d',' > traintemp2.csv
    elif [ $i -eq 11 ]
    then
            cat $trainFile | awk -F',' '{print $11}' | sed 's/^$/EMPTY/g' | paste traintemp2.csv - -d',' > traintemp1.csv # Fill empty Cabin data with EMPTY
    elif [ $i -eq 12 ]
    then
        cat $trainFile | awk -F',' '{print $12}' | sed 's/^[^A-Z]/EMPTY/g' | paste traintemp1.csv - -d',' > $outFile # Fill empty embark data with EMPTY
    else
            echo "No change to col $i"
    fi
done

rm traintemp1.csv
rm traintemp2.csv
echo "Done! File: $outFile is ready to be loaded into ROOT"
