#!/bin/bash

#stdin write or add content to the destination file
echo "This is sample text 1" > temp.txt 
echo "This is sample text 2" >> temp.txt

# stderr wirte or add the error info to the destination file
ls + 2> stderr.txt
cd dfd 2>> stderr.txt

# redirect the text block
# for example,"cat <<EOF>log.txt  ...... EOF" means the contents between "cat <<EOF>log.txt" and "EOF" will be redirected.
cat<<EOF>log.txt
LOG FILE HEADER
This is a test log file
Funciton: System statistics
EOF
