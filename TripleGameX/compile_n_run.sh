#!/bin/sh

g++ TripleGameX.cpp -o ./bin/triplex || exit 1

echo "File compiled successfully!"
echo "Executing Prgoram"
echo "----------------------------------"
./bin/triplex 3
echo "\n"
