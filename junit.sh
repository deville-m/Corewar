#!/bin/bash

ZAZ=./resources/corewar_sample
OUR=./corewar
SEQ=100000

if [ $# -eq 0 ]
  then
      echo "Usage: <champs> <opts: start>"
	  exit 1
fi
for i in `seq $2 $SEQ`; do
	diff <($OUR -d $i -n -1 "$1") <($ZAZ -d $i "$1")
	if [ $? != 0 ]
	then
	   exit 1
	fi
	echo "\ Correct for $i"
done
