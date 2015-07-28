#ifndef TOOLS
#define TOOLS

#include <gnome-keyring-1/gnome-keyring.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

int keyring_handle_error(GnomeKeyringResult res);

#endif
