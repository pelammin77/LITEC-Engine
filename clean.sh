#!/bin/bash

echo "Cleaning build artifacts..."

# Poista binääri- ja objektihakemistot
rm -rf bin bin-int

# Poista Premaken generoidut make-tiedostot ja projektit
rm -f Makefile
rm -f *.make
rm -f *.sln
rm -f *.vcxproj *.vcxproj.filters

echo "Clean complete."
