#ifndef PASSWORD
#define PASSWORD

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <gnome-keyring-1/gnome-keyring-memory.h>

extern const int PASSWORD_MAX_SIZE;

int read_password(char** password);
char *try_secure_dup(char *string);
char *try_secure_alloc(int size);
void free_password(char *password);

#endif
