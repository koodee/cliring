#ifndef ITEM
#define ITEM

#include <stdlib.h>
#include <string.h>
#include "tools.h"

/**
  @brief Creates a new item, or updates it if it already exists.

  @param keyring The keyring that will hold the item.
  @param password The password that will be stored in the item.
  @param display_name A name for the item.
  @param attributes A list of key/value couples that will identify the item.

  @return A gnome keyring error code.
*/
int password_store(const char *keyring, const char *password, const char *display_name, GnomeKeyringAttributeList *attributes);

/**
  @brief Search for an item in a keyring and displays its password.

  @param keyring The keyring that holds the item we are looking for.
  @param attributes The list of attributes that defines the item.

  @return A gnome keyring error code.
  */
int search(const char *keyring, GnomeKeyringAttributeList *attributes);

#endif
