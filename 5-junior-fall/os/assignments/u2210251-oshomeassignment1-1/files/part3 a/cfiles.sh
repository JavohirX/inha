#!/bin/bash
echo Files in your HOME Directory with extension .c
for FILE in $HOME/*.c
do
echo $FILE
done
