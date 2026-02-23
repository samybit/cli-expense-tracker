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

// Safely reads a double by first reading a string, then converting it
double read_double()
{
    char buffer[50];
    read_string(buffer, sizeof(buffer));
    return atof(buffer); // Convert string to float/double
}