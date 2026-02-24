#ifndef UTILS_H
#define UTILS_H

// ANSI Color Codes
#define COLOR_RESET   "\x1b[0m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_YELLOW  "\x1b[33m"

void read_string(char *buffer, int max_length);

// return 1 on success, 0 on failure, 
// and pass the actual value via a pointer.
int read_int(int *result);
int read_double(double *result);

#endif