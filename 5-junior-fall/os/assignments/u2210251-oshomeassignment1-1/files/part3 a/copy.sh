#!/bin/bash
echo Copying file $1 to $2
cp $1 $2
echo file $1 CONTENTS
cat $1
echo file $2 CONTENTS
cat $2
