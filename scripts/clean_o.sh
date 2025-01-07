#!/bin/bash

# Find and remove all .o files in the current directory and subdirectories
find . -type f -name "*.o" -exec rm -f {} \;

echo "All .o files have been removed."