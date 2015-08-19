#ifndef OPTIONS
#define OPTIONS

#include <gnome-keyring-1/gnome-keyring.h>
#include <stdlib.h>

/**
  @brief Holds all the informations given by the command line.
*/
struct cliring_option
{
  char *keyring; /// A keyring name.
  char *password; /// The password for the keyring or item to create.
  char *display_name; /// The display name of the item to create.
  GnomeKeyringAttributeList *attributes; /// A list of attributes.
  int attributes_count; /// Number of attributes found. Needed with we want to know if the attributes list is empty or not.
};
typedef struct cliring_option s_option;

/**
  @brief Inits the options structure with default values.

  @param options The option structure to initialize.
*/
void init_options(s_option* options);


void free_options(s_option* options);

#endif
