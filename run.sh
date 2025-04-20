#!/bin/bash

# Oletus: debug
CONFIG=${1:-debug}
BIN="./bin/${CONFIG^}/Sandbox"

if [ ! -f "$BIN" ]; then
    echo "Executable not found: $BIN"
    echo "Did you run build.sh with the correct configuration?"
    exit 1
fi

echo "Running Sandbox in '$CONFIG' mode..."
$BIN
