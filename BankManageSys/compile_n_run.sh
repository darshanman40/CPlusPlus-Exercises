#!/bin/sh

g++ main.cpp -o ./bin/bank_manage_system || exit 1

echo "File compiled successfully!"
echo "Executing Prgoram"
echo "----------------------------------"
./bin/bank_manage_system
echo "\n"
