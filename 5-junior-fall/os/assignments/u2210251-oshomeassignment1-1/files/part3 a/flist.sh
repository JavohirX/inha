#!/bin/bash
echo=====================================================
echo Do you want directory listing long or short \( enter 1 or 0 \)
read LONG
if [ $LONG -eq 1 ]
then
ls -la
else
ls
fi
