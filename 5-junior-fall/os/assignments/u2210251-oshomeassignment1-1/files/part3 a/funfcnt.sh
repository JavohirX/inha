#!/bin/bash
echo ENTER FILENAME
read fname
lines_in_file() {
cat $fname | wc -l
}
words_in_file() {
cat $fname | wc -w
}
bytes_in_file() {
cat $fname | wc -c
}
num_lines=$( lines_in_file )
echo The file $fname has $num_lines lines in it
num_words=$( words_in_file )
echo The file $fname has $num_words words in it
num_bytes=$( bytes_in_file )
echo The file $fname has $num_bytes bytes in it
