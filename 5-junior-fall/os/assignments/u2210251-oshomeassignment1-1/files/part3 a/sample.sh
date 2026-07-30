#!/bin/bash
echo Hi, What is your name
read NAME
echo Good Morning $NAME
echo =================================================
echo Your Home directory : $PWD
echo Environment variable PATH = $PATH
echo PRESS Enter KEY
read key
echo =================================================
echo RAM MEMORY SPACE INFO IN MEGA BYTES
free -m
echo PRESS Enter KEY
read key
echo =================================================
echo HARD DISK USAGE INFO
du -h
echo PRESS Enter KEY
read key
echo =================================================
echo HARD DISK SPACE INFO
df -h
echo PRESS Enter KEY
read key
echo =================================================
echo PROCESSES CURRENTLY RUNNING
ps -la
echo PRESS Enter KEY
read keyS
echo ==================================================
echo LINUX VERSION
uname -a
echo PRESS Enter KEY
read key
echo ==================================================
echo WHO ARE CURRENTLY LOGGED IN
who -a
echo PRESS Enter KEY
read key
echo ==================================================
read -p 'Login name:' LOGIN
read -sp 'Password:' PASS
echo \n
echo Your LOGIN NAME IS $LOGIN
echo Your PASSWORD IS $PASS
echo ==================================================
