#!/bin/bash
echo =================================================
echo Name of the Bash script - $0
echo How many arguments were passed to the Bash script - $#
echo All the arguments supplied to the bash script - $@
echo The exit status of the most recently run process $?
echo The process ID of the current script - $$
echo User Name of the user running the script - $USER
echo The hostname of the machine the script is running on - $HOSTNAME
echo The number of seconds since the script was started - $SECONDS
echo Current line number in the Bash script : $LINENO
echo Random number returned by the RANDOM variable - $RANDOM
echo VALUES OF ALL ENVIRONMENT VARIABLES SET UP IN THE CURRENT ENVIRONMENT
env | more
echo =================================================
