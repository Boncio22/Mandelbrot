#!/bin/bash

#SAVEIF=$IFS
#IFS=$(echo -en "\n\b")

cd Grafiki/

for file in $(ls *ppm)
do
  name=${file%%.ppm}
  convert $name.ppm $name.png
  echo "$name"
done

rm *.ppm

cd ..
