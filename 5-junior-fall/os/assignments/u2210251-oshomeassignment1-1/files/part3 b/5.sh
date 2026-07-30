#!/bin/bash
echo "Select an option:"
echo "1) Halt"
echo "2) Init 0 (Power off)"
echo "3) Init 6 (Reboot)"
echo "4) Poweroff"
echo "5) Reboot"
echo "6) Shutdown"

read choice

case $choice in
    1) halt ;;
    2) init 0 ;;
    3) init 6 ;;
    4) poweroff ;;
    5) reboot ;;
    6) shutdown now ;;
    *) echo "Invalid option." ;;
esac
