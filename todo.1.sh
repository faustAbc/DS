#!/bin/bash
set -ex

gcc -o fileRead fileRead.c
ls ./
ls ./
./fileRead

if gcc -o fileRead fileRead.c ; then
    echo "Compilation success"
    else
    echo "You are bad coder"
fi