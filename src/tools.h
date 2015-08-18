#ifndef TOOLS
#define TOOLS

#include <gnome-keyring-1/gnome-keyring.h>
#include <stdio.h>

/**
  @brief Displays the message corresponding to a Gnoe error code.

  @param res The error code to treat.
  @return The error code that was passed.
*/
int keyring_handle_error(GnomeKeyringResult res);

#endif
