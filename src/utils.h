#ifndef UTILS_H
#define UTILS_H

void read_string(char *buffer, int max_length);

// return 1 on success, 0 on failure, 
// and pass the actual value via a pointer.
int read_int(int *result);
int read_double(double *result);

#endif