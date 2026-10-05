// Electricity Units Counter (C++)
// Calculates electricity units consumed and the bill from meter readings.
// Includes input validation. Rates below are SAMPLE slab rates - change them
// to match your own electricity tariff.
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

const int SLAB1_LIMIT = 100;
const int SLAB2_LIMIT = 200;
const int SLAB3_LIMIT = 300;

const double RATE1 = 10.0;   // Rs per unit, units 1-100
const double RATE2 = 15.0;   // Rs per unit, units 101-200
const double RATE3 = 20.0;   // Rs per unit, units 201-300
const double RATE4 = 25.0;   // Rs per unit, above 300

// Reads a non-negative whole number; keeps asking until input is valid.
int readUnits(const string &prompt)
{
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0 && cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) {
            return 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a whole number (0 or more).\n";
    }
}

// Returns the total charges for the given number of units.
double calculateCharges(int units)
{
    double total = 0.0;
    int remaining = units;
    int slab;

    slab = (remaining > SLAB1_LIMIT) ? SLAB1_LIMIT : remaining;
    total += slab * RATE1;
    remaining -= slab;

    slab = (remaining > (SLAB2_LIMIT - SLAB1_LIMIT)) ? (SLAB2_LIMIT - SLAB1_LIMIT) : remaining;
    total += slab * RATE2;
    remaining -= slab;

    slab = (remaining > (SLAB3_LIMIT - SLAB2_LIMIT)) ? (SLAB3_LIMIT - SLAB2_LIMIT) : remaining;
    total += slab * RATE3;
    remaining -= slab;

    total += remaining * RATE4;
    return total;
}

int main()
{
    char again;

    cout << "=== Electricity Units Counter ===\n";

    do {
        int previous = readUnits("\nEnter previous meter reading: ");
        int current = readUnits("Enter current meter reading : ");

        if (current < previous) {
            cout << "Error: current reading cannot be less than previous reading.\n";
        } else {
            int units = current - previous;
            double charges = calculateCharges(units);
            cout << "\n--- Bill Summary ---\n";
            cout << "Units consumed : " << units << "\n";
            cout << "Total charges  : Rs " << fixed << setprecision(2) << charges << "\n";
        }

        cout << "\nCalculate another bill? (y/n): ";
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (again == 'y' || again == 'Y');

    cout << "Thank you!\n";
    return 0;
}
