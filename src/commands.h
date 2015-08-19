#ifndef COMMANDS
#define COMMANDS

#include "options.h"
#include "password.h"
#include "keyring.h"
#include "item.h"

/*
  Checks that options are correctly set and launches the keyring creation function.
*/
int execute_create(const s_option *opt);

/*
  Checks that options are correctly set and launches the keyring listing function.
*/
int execute_list(const s_option *opt);

/*
  Checks that options are correctly set and launches the store password function.
*/
int execute_store(s_option *opt);

/*
  Checks that options are correctly set and launches the retrieve password function.
*/
int execute_get(s_option *opt);

int execute_lock(s_option *opt);

int execute_unlock(s_option *opt);

#endif
