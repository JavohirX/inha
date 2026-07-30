#!/bin/bash

# Input: tree output file
# Output: kernel_tree.dot (Graphviz .dot file)

input_file=$1
output_file="kernel_tree.dot"
indent_level=0

# Initialize an array to hold the directory stack
declare -a dir_stack

# Start the Graphviz .dot format
echo "digraph G {" > $output_file

# Read each line from the tree output
while IFS= read -r line; do
    # Strip leading tree characters and extract directory names
    cleaned_line=$(echo "$line" | sed -E 's/^[│└├─ ]+//')

    # Count how deep we are in the directory structure by counting indents
    new_indent_level=$(echo "$line" | grep -o "│   " | wc -l)

    # If we are moving to a new level deeper in the directory structure
    if [ $new_indent_level -gt $indent_level ]; then
        dir_stack+=("$parent_dir")
    fi

    # If we are moving up in the structure, pop from the stack
    if [ $new_indent_level -lt $indent_level ] && [ ${#dir_stack[@]} -gt 0 ]; then
        # Remove the last directory from the stack
        dir_stack=("${dir_stack[@]:0:${#dir_stack[@]}-1}")
    fi

    # Set the parent directory to the last item in the stack, if available
    if [ ${#dir_stack[@]} -gt 0 ]; then
        parent_dir="${dir_stack[-1]}"
    else
        parent_dir="root"
    fi

    # Set the current directory name
    current_dir="$cleaned_line"

    # If there is a parent directory, create an edge
    if [ ! -z "$parent_dir" ] && [ "$parent_dir" != "$current_dir" ]; then
        echo "  \"$parent_dir\" -> \"$current_dir\";" >> $output_file
    fi

    # Update the parent directory and indent level for the next iteration
    parent_dir=$current_dir
    indent_level=$new_indent_level
done < "$input_file"

# End the Graphviz .dot format
echo "}" >> $output_file
