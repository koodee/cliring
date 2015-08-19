#ifndef KEYRING
#define KEYRING

#include <string.h>
#include "tools.h"

/*
  Creates a new keyring from a name and a password.
*/
int keyring_create(char *keyring, char *password);

/*
  Lists all existing keyrings.
*/
int keyrings_list();

int keyring_lock(char *keyring);

char *get_default_keyring();



#endif
