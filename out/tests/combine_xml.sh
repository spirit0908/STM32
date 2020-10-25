#!/bin/sh

OUTPUT_FILE=$1
TMP_FILE=$1.tmp

rm -f OUTPUT_FILE
#mv OUTPUT_FILE OUTPUT_FILE.sav

echo "<?xml version=\"1.0\"?>" >> $TMP_FILE
echo "<span>" >> $TMP_FILE

FILES=*.xml

#Read each xml file in the current foder
for i in $FILES
do

echo "process file: $i"



  #Read each line and remove xml header and footer (lines with "xml" or "span")
  while read -r line
  do
    if [[ $line != *"xml"* ]] && [[ $line != *"span"* ]] ; 
    then
      echo $line >> $TMP_FILE;
    fi
  done < "$i"
done

echo "</span>" >> $TMP_FILE

mv $TMP_FILE $OUTPUT_FILE
