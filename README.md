# Electricity Units Counter

A console program written in C and C++ that calculates electricity units consumed and the bill from meter readings.

## Features
- Takes previous and current meter readings
- Validates input (rejects letters, negative numbers, and a current reading lower than the previous one)
- Calculates charges using slab rates
- Lets the user calculate more than one bill

## How to run
C: gcc electricity_units_counter.c -o counter
C++: g++ electricity_units_counter.cpp -o counter

## Note
The slab rates in the code are sample values and can be changed.
