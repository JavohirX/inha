#!/bin/bash
echo =================================================
A=1
B=1
echo Computing FACTORIAL OF n
echo -n ENTER VALUE OF n=
read n
until [ $A -gt $n ]
do
B=$(expr $B \* $A)
A=$(expr $A + 1)
done
echo FACTORIAL OF $n = $B
