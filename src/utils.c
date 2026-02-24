#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

// Safely reads a string and strips the trailing newline character
void read_string(char *buffer, int max_length)
{
    if (fgets(buffer, max_length, stdin) != NULL)
    {
        // Find the newline character and replace it with null terminator
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
    }
}

int read_int(int *result)
{
    char buffer[50];
    read_string(buffer, sizeof(buffer));

    char *endptr;
    // strtol converts string to long, base 10
    long val = strtol(buffer, &endptr, 10);

    // If endptr points to the start, no digits were found.
    // If *endptr is not '\0', they typed mixed garbage like "12abc".
    if (endptr == buffer || *endptr != '\0')
    {
        return 0; // Failure
    }

    *result = (int)val;
    return 1; // Success
}

// Safely reads a double by first reading a string, then converting it
int read_double(double *result)
{
    char buffer[50];
    read_string(buffer, sizeof(buffer));

    char *endptr;
    double val = strtod(buffer, &endptr);

    if (endptr == buffer || *endptr != '\0')
    {
        return 0; // Failure
    }

    *result = val;
    return 1; // Success
}