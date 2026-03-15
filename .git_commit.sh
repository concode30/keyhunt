#!/bin/bash

# Git commit script - adds and commits all changes individually

# Get list of all modified files
git status --porcelain | grep '^ M' | awk '{print $2}' | while read -r file; do
    echo "Committing: $file"
    git add "$file"
    git commit -m "Update $file"
done

# Handle new files
git status --porcelain | grep '^??' | awk '{print $2}' | while read -r file; do
    echo "Adding and committing new file: $file"
    git add "$file"
    git commit -m "Add $file"
done

echo "Done!"
# Push to remote repository
git push origin main
