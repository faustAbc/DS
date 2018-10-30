#!/bin/bash

set -ex

i=0

fileName=getTime

while [[ i -lt 50 ]];
do

rm -f $fileName;

gcc -o ${fileName} ${fileName}.c || true;

if [ -e ${fileName} ]; then
    echo "Compilation success"
else
    echo "You are bad coder"
fi

i=`expr $i + 1`

done
