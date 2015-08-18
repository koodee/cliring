#ifndef PASSWORD
#define PASSWORD

#include <stdio.h>
#include <termios.h>
#include <string.h>

extern const int PASSWORD_MAX_SIZE;

int read_password(char** password);

#endif
