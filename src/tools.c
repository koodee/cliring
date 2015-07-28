#include "tools.h"

int keyring_handle_error(GnomeKeyringResult res)
{
  if (res == GNOME_KEYRING_RESULT_OK)
      return res;

  fprintf(stderr, "An error occured: %s\n", gnome_keyring_result_to_message(res));
  return res;
}
