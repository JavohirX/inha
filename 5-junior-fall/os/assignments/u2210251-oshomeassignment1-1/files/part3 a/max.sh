#!/bin/bash
list=(12 67 123 49 88 123 -9 0 456 126)
let I=0
max=${list[0]}
let I=+$I
while [ $I -le 9 ]
do
if [ ${list[$I]} -gt $max ]
then
max=${list[$I]}
fi
let I=$I+1
done
echo Maximum element in the list is : $max
