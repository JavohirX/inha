#!/bin/bash

# File to modify
file="listdir"

# New line to insert
new_line="Hi, this new line has been inserted here"

# Check if the file exists
if [ ! -f "$file" ]; then
    echo "Error: File '$file' does not exist."
    exit 1
fi

# Check if the file has at least 6 lines
if [ $(wc -l < "$file") -lt 6 ]; then
    echo "Error: File '$file' has fewer than 6 lines."
    exit 1
fi

# Replace the 6th line
sed -i '6s/.*'"/$new_line"'/' "$file"

echo "The 6th line in '$file' has been replaced successfully."
