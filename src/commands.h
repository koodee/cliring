#ifndef COMMANDS
#define COMMANDS

#include <stdio.h>
#include <string.h>
#include "options.h"
#include "password.h"
#include "keyring.h"

// Executes a command based on its name and an options structure
int execute_command(const char *command, const s_option *opt);

#endif
