#include "keyring.h"

int keyring_handle_error(GnomeKeyringResult res)
{
  fprintf(stderr, "An error occured: %s\n", gnome_keyring_result_to_message(res));
  return res;
}

int keyring_create(char *keyring, char *password)
{
  GnomeKeyringResult res = gnome_keyring_create_sync(keyring, password);
  if (res != GNOME_KEYRING_RESULT_OK)
  {
    return keyring_handle_error(res);
  }

  return 0;
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
