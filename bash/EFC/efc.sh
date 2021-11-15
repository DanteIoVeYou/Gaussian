#!/bin/bash
ls *.com.log > target.log
line=$((cat target.log)|wc -l)
for((i=1;i<="$line";i=i+1))
do
    name=$(cat target.log|awk 'NR=='$i' {print $1}')
    ./FEC.exe "$name" 
done

echo "Done"

