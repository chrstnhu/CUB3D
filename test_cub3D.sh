#!/bin/bash

# Path to the directory containing test files
MAPS_DIR="maps/bad"

# Path to your cub3D program (adjust according to your setup)
CUB3D_EXEC="./cub3D"

# Valgrind options (adjust if needed)
VALGRIND_OPTIONS="--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=1"

# Initialize counters for passed and failed tests
passed_count=0
failed_count=0

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Loop through each .cub file in the directory
for map_file in $MAPS_DIR/*.cub; do
    echo -e "${YELLOW}Testing file: $map_file${NC}"

    # Execute the program with Valgrind and capture the output
    output=$(valgrind $VALGRIND_OPTIONS $CUB3D_EXEC $map_file 2>&1)

    # Display the complete Valgrind output in the terminal
    echo "$output"

    # Check if the output contains "Error :" and if Valgrind reports no leaks
    if echo "$output" | grep -q "Error :" && echo "$output" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}PASSED${NC}"
        ((passed_count++))
    else
        echo -e "${RED}FAILED${NC}"
        ((failed_count++))
    fi

    # Add a separation between tests
    echo ""
    echo "-------------------------------------------------------"
done

# Display the summary of results
echo -e "\nAll Valgrind tests are completed."
echo -e "${GREEN}Number of tests passed: $passed_count${NC}"
echo -e "${RED}Number of tests failed: $failed_count${NC}"

