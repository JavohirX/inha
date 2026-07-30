#!/bin/bash
echo =================================================
A=1
B=0
C=1
echo Computing SUM OF FIRST n ODD INTEGERS
echo ENTER VALUE OF n=
read n
while [ $A -le $n ]
do
B=$(expr $B + $C)
A=$(expr $A + 1)
C=$(expr $C + 2)
done
echo Sum of FIRST $n odd numbers = $B
