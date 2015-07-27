#ifndef OPTIONS
#define OPTIONS
#include <stdbool.h>

struct cliring_option
{
  bool list;
  char *keyring;
  char *password;
  char *display_name;
};
typedef struct cliring_option s_option;

#endif
