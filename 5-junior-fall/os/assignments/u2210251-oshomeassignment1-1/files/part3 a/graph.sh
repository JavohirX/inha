#!/bin/bash

# Check if a directory is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

base_dir="$1"

# Function to execute commands in each subdirectory
process_directory() {
    local dir="$1"

    echo "Processing directory: $dir"

    # Change to the target directory
    cd "$dir" || return

    # Execute commands
    tree -a -d -L 2 > kernel_directory_tree.txt
    ./tree-to-dot.sh kernel_directory_tree.txt
    dot -Tpdf kernel_tree.dot -o a1.pdf

    # Return to the base directory
    cd - > /dev/null || return
}

# Export the function for use with find
export -f process_directory

# Use find to traverse directories and execute the function
find "$base_dir" -type d -exec bash -c 'process_directory "$0"' {} \;

echo "Processing completed."

