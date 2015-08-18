#ifndef COMMANDS
#define COMMANDS

#include <stdio.h>
#include <string.h>
#include "options.h"
#include "password.h"
#include "keyring.h"
#include "item.h"

int execute_create(const s_option *opt);
int execute_list(const s_option *opt);
int execute_store(const s_option *opt);
int execute_get(const s_option *opt);

#endif
