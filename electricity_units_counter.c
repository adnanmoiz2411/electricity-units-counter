/*
 * Electricity Units Counter (C)
 * Calculates electricity units consumed and the bill from meter readings.
 * Includes input validation. Rates below are SAMPLE slab rates - change them
 * to match your own electricity tariff.
 */
#include <stdio.h>
#include <string.h>

#define SLAB1_LIMIT 100
#define SLAB2_LIMIT 200
#define SLAB3_LIMIT 300

#define RATE1 10.0   /* Rs per unit, units 1-100   */
#define RATE2 15.0   /* Rs per unit, units 101-200 */
#define RATE3 20.0   /* Rs per unit, units 201-300 */
#define RATE4 25.0   /* Rs per unit, above 300     */

/* Reads a non-negative whole number; keeps asking until input is valid. */
int read_units(const char *prompt)
{
    char line[64];
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 0;
        }
        if (sscanf(line, "%d %c", &value, &extra) == 1 && value >= 0) {
            return value;
        }
        printf("Invalid input. Please enter a whole number (0 or more).\n");
    }
}

/* Returns the total charges for the given number of units. */
double calculate_charges(int units)
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

int main(void)
{
    char again[16];
    int previous, current, units;
    double charges;

    printf("=== Electricity Units Counter ===\n");

    do {
        previous = read_units("\nEnter previous meter reading: ");
        current = read_units("Enter current meter reading : ");

        if (current < previous) {
            printf("Error: current reading cannot be less than previous reading.\n");
        } else {
            units = current - previous;
            charges = calculate_charges(units);
            printf("\n--- Bill Summary ---\n");
            printf("Units consumed : %d\n", units);
            printf("Total charges  : Rs %.2f\n", charges);
        }

        printf("\nCalculate another bill? (y/n): ");
        if (fgets(again, sizeof(again), stdin) == NULL) {
            break;
        }
    } while (again[0] == 'y' || again[0] == 'Y');

    printf("Thank you!\n");
    return 0;
}
