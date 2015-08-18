#ifndef OPTIONS
#define OPTIONS

#include <gnome-keyring-1/gnome-keyring.h>

struct cliring_option
{
  char *keyring;
  char *password;
  char *display_name;
  GnomeKeyringAttributeList *attributes;
  int attributes_count;
};
typedef struct cliring_option s_option;

void init_options(s_option* options);

#endif
