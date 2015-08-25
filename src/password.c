#include "password.h"

const int PASSWORD_MAX_SIZE = 64;


// Code from http://stackoverflow.com/questions/1196418/getting-a-password-in-c-without-using-getpass-3
int read_password(char **password, char *text)
{
  struct termios oflags, nflags;

    /* disabling echo */
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        return 1;
    }

    printf("%s: ", text);
    fgets(*password, PASSWORD_MAX_SIZE, stdin);
    (*password)[strlen(*password) - 1] = 0;

    /* restore terminal */
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        return 1;
    }

    return 0;
}

char *try_secure_dup(char *string)
{
  char *dup_string = NULL;

  dup_string  = gnome_keyring_memory_strdup(string);

  // No secure paging available, we do a strdup
  if (!dup_string)
    dup_string = (char *) strdup(string);


  return dup_string;
}

char *try_secure_alloc(int size)
{
  if (size <= 0)
    return NULL;

  char *res = NULL;

  res = (char *) gnome_keyring_memory_try_alloc(size);

  if (!res)
    res = malloc(size);

  return res;
}

void free_password(char *password)
{
  if (gnome_keyring_memory_is_secure(password))
    gnome_keyring_memory_free(password);
  else
    free(password);
}
