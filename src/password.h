#ifndef PASSWORD
#define PASSWORD

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <gnome-keyring-1/gnome-keyring-memory.h>

extern const int PASSWORD_MAX_SIZE;

/**
  @brief Read a password from stdin

  @param password A pointer to a string that will hold the password.
  @param text The text to prompt.
  @return 1 if an error occured, 0 otherwise.
*/
int read_password(char **password, char *text);

/**
  @brief Duplicates a string to non paged memory if possible.

  If supported by the system, the string will be written to a secure non paged memory space.
  If not, it will be duplicated with strdup.

  Use free_password to free the memory.

  @param string The string to duplicate.
  @return The duplicated string.
*/
char *try_secure_dup(char *string);

/**
  @brief Allocate non paged memory if possible.

  If supported by the system, space is allocated to a secure non paged space.
  If not, it will be allocated with malloc.

  Use free_password to free the memory.

  @param size The memory size to allocate.
  @return A pointer to the allocated memory.
*/
char *try_secure_alloc(int size);

/**
  @brief Free memory allocated via try_secure_alloc or try_secure_dup.

  @param password Pointer to the memory space to free;
*/
void free_password(char *password);

#endif
