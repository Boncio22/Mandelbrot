#!/bin/bash

#SAVEIF=$IFS
#IFS=$(echo -en "\n\b")

cd Grafiki/

for plik in $(ls *ppm)
do
  liczba=$(($liczba+1))
done

liczba=$(($liczba -1))

for file in $(ls *ppm)
do
  name=${file%%.ppm}
  convert $name.ppm $name.png
  echo "$name / $liczba"
  rm $name.ppm
done

echo "GOTOWE!"

cd ..
