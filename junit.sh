#!/bin/bash

ZAZ=./resources/corewar_sample
OUR=./corewar
SEQ=100000

if [ $# -eq 0 ]
  then
      echo "Usage: <champs> <opts: start>"
	  exit 1
fi
for i in `seq $3 $SEQ`; do
	$OUR -d $i -n -1 -n -2 "$1" "$2" > a.bite
	$ZAZ -d $i "$1" "$2" > b.bite
	diff a.bite b.bite
#	diff <( $OUR -d $i -n -1 -n -2 "$1" "$2" ) <( $ZAZ -d $i "$1" "$2" )
	if [ $? != 0 ]
	then
	   exit 1
	fi
	echo "\ Correct for $i"
done
