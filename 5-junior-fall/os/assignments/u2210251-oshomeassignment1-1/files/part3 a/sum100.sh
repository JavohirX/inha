#!/bin/bash
echo COMPUTING SUM OF FIRST 100 INTEGERS
sum=0
for i in {1..100}
do
sum=$sum+$i
done
echo SUM OF FIRST 100 INTEGERS = $sum
