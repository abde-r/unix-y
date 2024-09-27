#!/bin/sh

# Define the paths for the executable and temporary files
CUSTOM_LS_EXEC="./ft_ls -l"  # Path to your custom executable (change this to the correct path)
DIR_PATH="$1"                 # Directory to list (passed as an argument)
CUSTOM_LS_OUTPUT="ft_ls_output.txt"
SYSTEM_LS_OUTPUT="system_ls_output.txt"

# Check if the directory path is provided
if [ -z "$DIR_PATH" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

# Run the custom executable and store its output in a file
$CUSTOM_LS_EXEC "$DIR_PATH" > "$CUSTOM_LS_OUTPUT"

# Run the system ls command and store its output in a file
ls -l "$DIR_PATH" > "$SYSTEM_LS_OUTPUT"

# Compare the outputs and print the differences
diff "$CUSTOM_LS_OUTPUT" "$SYSTEM_LS_OUTPUT"

# Clean up temporary files
rm "$CUSTOM_LS_OUTPUT" "$SYSTEM_LS_OUTPUT"
