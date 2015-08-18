#ifndef KEYRING
#define KEYRING

#include "tools.h"

/*
  Creates a new keyring from a name and a password.
*/
int keyring_create(char *keyring, char *password);

/*
  Lists all existing keyrings.
*/
int keyrings_list();

#endif
