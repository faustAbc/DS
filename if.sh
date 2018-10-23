#!/bin/bash
set -ex

fileName=getTime

rm -f $fileName;

gcc -o ${fileName} ${fileName}.c || true;

if test -e ${fileName}; then
    echo "Compilation success"
else
    echo "You are bad coder"
fi
