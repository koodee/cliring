#include "item.h"

int password_store(const char *keyring, const char *password, const char *display_name, GnomeKeyringAttributeList *attributes)
{
  guint32 item_id;

  GnomeKeyringResult res = gnome_keyring_item_create_sync(keyring,
                                                          GNOME_KEYRING_ITEM_GENERIC_SECRET,
                                                          display_name,
                                                          attributes,
                                                          password,
                                                          TRUE,
                                                          &item_id);

  gnome_keyring_attribute_list_free(attributes);
  return keyring_handle_error(res);
}

int search(const char *keyring, GnomeKeyringAttributeList *attributes)
{
  GList *found = malloc(sizeof(GList));

  GnomeKeyringResult res = gnome_keyring_find_items_sync(GNOME_KEYRING_ITEM_GENERIC_SECRET, attributes, &found);
  if (res != GNOME_KEYRING_RESULT_OK)
  {
    gnome_keyring_found_list_free(found);
    return keyring_handle_error(res);
  }

  while (found != NULL && strcmp(((GnomeKeyringFound *)found->data)->keyring, keyring))
  {
    found = found->next;
  }

  if (found)
  {
    GnomeKeyringFound *data = found->data;
    printf("%s\n", data->secret);
  }
  else
  {
    gnome_keyring_found_list_free(found);
    return keyring_handle_error(GNOME_KEYRING_RESULT_NO_MATCH);
  }

  gnome_keyring_found_list_free(found);
  return 0;
}
