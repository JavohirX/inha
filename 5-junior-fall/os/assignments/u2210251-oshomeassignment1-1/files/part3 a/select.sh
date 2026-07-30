#!/bin/bash
#A simple Menu System
OPTIONS='ls longls who free linuxversion cat mv cp QUIT'
PS3='Choose an option:'
select CHOICE in $OPTIONS
do
if [ $CHOICE == ls ]
then
ls
elif [ $CHOICE == longls ]
then
ls -la
elif [ $CHOICE == who ]
then
who -a
elif [ $CHOICE == free ]
then
free
elif [ $CHOICE == linuxversion ]
then
uname -a
elif [ $CHOICE == cat ]
then
echo -n ENTER FILE NAME :
read FILE
cat $FILE
elif [ $CHOICE == mv ]
then
echo -n ENTER OLD FILE NAME :
read FILE1
echo -n ENTER NEW FILE NAME :
read FILE2
mv $FILE1 $FILE2
elif [ $CHOICE == cp ]
then
echo -n ENTER NAME OF FILE TO BE COPIED FROM:
read FILE1
echo -n ENTER NAME OF FILE TO BE COPIED TO :
read FILE2
cp $FILE1 $FILE2
elif [ $CHOICE == QUIT ]
then
echo BYE ... BYE
break
fi
done
