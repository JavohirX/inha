#!/bin/bash
#Menu Driven program to perform listed operations
loop=1
while [ $loop -eq 1 ]
do
echo .........................................................
echo .                         MENU                          .
echo .                                                       .
echo . 1. LIST DIRECTORY CONTENTS                            .
echo . 2. SHOW CURRENT WORKING DIRECTORY                     .
echo . 3. DISPLAY LINUX VERSION                              .
echo . 4. SHOW FREE SPACE ON DISK                            .
echo . 5. SHOW WHO ARE LOGGED IN                             .
echo . 6. DISPLAY CONTENTS OF A FILE                         .
echo . 7. CREATE OR OPEN A FILE                              .
echo . 8. COPY A FILE                                        .
echo . 9. RENAME A FILE                                      .
echo . 10. REMOVE A FILE                                     .
echo . 11. QUIT                                              .
echo .........................................................
echo ENTER YOUR CHOICE :
read CH
case $CH in
1)
ls
;;
2)
pwd
;;
3)
uname -r
;;
4)
free
;;
5)
who -a
;;
6)
echo -n Enter File Name :
read FILE
cat $FILE
;;
7)
echo -n Enter File Name :
read FILE
gedit $FILE
;;
8)
echo -n Enter Name of the File to be copied from :
read FILE1
echo -n Enter Name of the File to be copied to :
read FILE2
cp $FILE1 $FILE2
;;
9)
echo -n Enter OLD File Name:
read FILE1
echo -n Enter NEW File Name:
read FILE2
mv $FILE1 $FILE2
;;
10)
echo -n Enter Name of the File to delete:
read FILE
echo -n ARE YOU SURE - CONFIRM 1 OR 0 
read OK
if [ $OK -eq 1 ]
	then
		rm $FILE
		echo File $FILE deleted.....OK
	else
		echo File $FILE not deleted.....OK
fi
;;
11)
echo QUITING.......GOOD BYE
break
;;
*)
echo INVALID CHOICE - READ MENU CORRECTLY
;;
esac
done
