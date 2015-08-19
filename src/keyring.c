#include "keyring.h"

int keyring_create(char *keyring, char *password)
{
  GnomeKeyringResult res = gnome_keyring_create_sync(keyring, password);

  return keyring_handle_error(res);
}

int keyrings_list()
{
  GList *keyrings;

  GnomeKeyringResult res = gnome_keyring_list_keyring_names_sync(&keyrings);
  if (res != GNOME_KEYRING_RESULT_OK)
  {
    return keyring_handle_error(res);
  }

  for (GList *l = keyrings; l != NULL; l = l->next)
  {
    printf("%s\n", (char *) l->data);
  }

  return 0;
}

char *get_default_keyring()
{
  char *default_keyring;
  char *default_keyring_dup;
  GnomeKeyringResult res = gnome_keyring_get_default_keyring_sync(&default_keyring);

  // An error occured
  if (res != GNOME_KEYRING_RESULT_OK)
  {
    keyring_handle_error(res);
    return NULL;
  }

  // There is no default keyring
  if (!default_keyring)
  {
    fprintf(stderr, "No default keyring found. Please set one or use the -k option.\n");
    return NULL;
  }

  // Default_keyring has been created via a g_malloc so it must be cleaned with g_free.
  // I duplicated the variable to allow the caller to clean it with a free.
  default_keyring_dup = strdup(default_keyring);
  g_free(default_keyring);

  return default_keyring_dup;
}
