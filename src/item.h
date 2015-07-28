#ifndef ITEM
#define ITEM

#include <gnome-keyring-1/gnome-keyring.h>
#include <glib.h>
#include <stdlib.h>
#include "tools.h"

int password_store(const char *keyring, const char *password, const char *display_name);

#endif
