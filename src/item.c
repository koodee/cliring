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
