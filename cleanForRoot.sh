#!/bin/bash
# Script for cleaning up the titanic dataset for ROOT

trainFile="data/train.csv"
outFile="data/training.csv"

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
#sed -i '1d' $trainFile # Remove the column headers
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
    then # Make two cabin cols one for the letter, one for the number
        cat $trainFile | awk -F',' '{print $11}' | sed 's/[0-9]//g' | sed 's/\ [A-Z]//g' | sed 's/^$/n/g' | sed 's/Cabin/Section/g' | paste traintemp2.csv - -d',' > traintemp1.csv # Fill empty Cabin data with EMPTY
        cat $trainFile | awk -F',' '{print $11}' | sed 's/[A-Z]//g' | sed 's/^\ //g' | sed 's/\ [0-9]*//g' | sed 's/^$/-2/g' | sed 's/abin/Room/g' | paste traintemp1.csv - -d',' > traintemp2.csv
    elif [ $i -eq 12 ]
    then # issue with this below line comes from the data file itself, if set to use windows end line commands it will give issues. Easiest solution is to open the train.csv file in VS Code and change file type to LF instead of CRLF
        cat $trainFile | awk -F',' '{print $12}' | sed 's/^$/E/g' | paste traintemp2.csv - -d',' > $outFile # Fill empty embark data with EMPTY (sometimes this line breaks add [[:space:]] between ^ and $ or remove it if its not working)
    else
            echo "No change to col $i"
    fi
done

rm traintemp1.csv
rm traintemp2.csv
echo "Done! File: $outFile is ready to be loaded into ROOT"
