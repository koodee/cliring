#ifndef OPTIONS
#define OPTIONS
#include <stdlib.h>

struct cliring_option
{
  char *keyring;
  char *password;
  char *display_name;
};
typedef struct cliring_option s_option;

void init_options(s_option* options);

#endif
