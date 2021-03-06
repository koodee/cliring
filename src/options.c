#include "options.h"

void init_options(s_option *options)
{
  if (options != NULL)
  {
    options->keyring = NULL;
    options->display_name = NULL;
    options->attributes = gnome_keyring_attribute_list_new();
    options->attributes_count = 0;
  }
}

void free_options(s_option *options)
{
  free(options->keyring);
  gnome_keyring_attribute_list_free(options->attributes);
  free(options);
}
