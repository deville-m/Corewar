#! /bin/bash

i=0
diff <(./corewar -d $i -n -1 "$@") <(./resources/corewar_sample -d $i "$@")
while [ $? -ne 0 ]
do
	i=$((i+1))
	diff <(./corewar -d $i "$@") <(./resources/corewar_sample -d $i "$@")
done
