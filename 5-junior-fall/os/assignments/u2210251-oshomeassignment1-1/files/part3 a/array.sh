#!/bin/bash
list=(12 67 123 49 88 123 -9 0 456 126)
let I=0
while [ $I -le 9 ]
do
echo ${list[$I]}
let I=$I+1
done
