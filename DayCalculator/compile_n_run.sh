#!/bin/sh

g++ main.cpp -o ./bin/day_calculator || exit 1

echo "File compiled successfully!"
echo "Executing Prgoram"
echo "----------------------------------"
./bin/day_calculator
echo "\n"
