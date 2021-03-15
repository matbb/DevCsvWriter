#!/bin/bash

g++ -o main.out main.cpp -lm
./main.out
python3 ./plot.py
