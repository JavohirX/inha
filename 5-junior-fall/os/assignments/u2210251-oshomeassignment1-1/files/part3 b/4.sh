#!/bin/bash

# Function to display file contents
display_file() {
    echo "Contents of $1:"
    cat "$1"
    echo "------------------------"
    echo "                        "
}

# Check if part2q exists
if [ ! -f "part2q" ]; then
    echo "Error: File 'part2q' does not exist."
    exit 1
fi

echo "Original content of part2q:"
display_file part2q

# (i) Convert lowercase to uppercase
tr '[:lower:]' '[:upper:]' < part2q > part2ql
echo "After converting lowercase to uppercase:"
display_file part2ql

# (ii) Convert uppercase to lowercase
tr '[:upper:]' '[:lower:]' < part2q > part2qu
echo "After converting uppercase to lowercase:"
display_file part2qu

# (iii) Replace 'commands' with 'COMMANDS' and 'the' with 'THE' in lines containing 'commands'
sed '/commands/s/commands/COMMANDS/g; /commands/s/\bthe\b/THE/g' part2q > part2qr
echo "After replacing 'commands' and 'the':"
display_file part2qr

# (iv) Copy part2q to part2m, then delete first and last lines
cp part2q part2m
sed -i '1d;$d' part2m
echo "After deleting first and last lines:"
display_file part2m

# (v) Concatenate all files
cat part2q part2ql part2qu part2qr part2m > part2qa
echo "After concatenating all files:"
display_file part2qa

echo "All operations completed successfully."
