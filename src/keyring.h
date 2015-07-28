#ifndef KEYRING
#define KEYRING

#include <gnome-keyring-1/gnome-keyring.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Creates a new keyring from a name and a password.
int keyring_create(char *keyring, char *password);

// Lists all existing keyrings.
int keyrings_list();

#endif
