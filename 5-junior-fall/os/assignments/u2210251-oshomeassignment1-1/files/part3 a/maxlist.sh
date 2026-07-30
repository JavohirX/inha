#!/bin/bash
echo -n Enter size of the list :
read N
echo Enter a list of $N numbers :
let K=0
while [ $K -lt $N ]
do
read VAL
list[$K]=$VAL
let K=$K+1
done
let I=0
max=${list[0]}
let I=+$I
while [ $I -lt $N ]
do
if [ ${list[$I]} -gt $max ]
then
max=${list[$I]}
fi
let I=$I+1
done
echo Maximum element in the list is : $max
