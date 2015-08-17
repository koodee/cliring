#ifndef OPTIONS
#define OPTIONS
#include <stdlib.h>
#include "keyring.h"

struct cliring_option
{
  char *keyring;
  char *password;
  char *display_name;
  GnomeKeyringAttributeList *attributes;
};
typedef struct cliring_option s_option;

void init_options(s_option* options);

#endif
