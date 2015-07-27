#ifndef KEYRING
#define KEYRING

#include <gnome-keyring-1/gnome-keyring.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int keyring_create(char *keyring, char *password);
int keyrings_list();

#endif
