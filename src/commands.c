#include "commands.h"

int execute_create(const s_option *opt)
{
  if (!opt->keyring)
  {
    fprintf(stderr, "You must provide a name for the new keyring.\n");
    return 1;
  }
  else
  {
    char *password = malloc(sizeof(char) * PASSWORD_MAX_SIZE);

    if (opt->password)
      password = strncpy(password, opt->password, PASSWORD_MAX_SIZE);
    else
      read_password(&password);

    int result = keyring_create(opt->keyring, password);

    free(password);
    return result;
  }
}

int execute_list(const s_option *opt)
{
  return keyrings_list();
}

int execute_store(const s_option *opt)
{
  if (!opt->keyring)
  {
    //TODO : use default keyring
    fprintf(stderr, "You must provide a keyring.\n");
    return 1;
  }
  if (!opt->display_name)
  {
    fprintf(stderr, "You must provide a display name for the password\n");
    return 1;
  }

  char *password = malloc(sizeof(char) * PASSWORD_MAX_SIZE);

  if (opt->password)
    password = strncpy(password, opt->password, PASSWORD_MAX_SIZE);
  else
    read_password(&password);

  //return password_store(opt->keyring, password, opt->display_name);
  free(password);
  return 0;
}

int execute_command(const char *command, const s_option *opt)
{
  if (!strcmp(command, "list"))
  {
    return execute_list(opt);
  }
  else if (!strcmp(command, "create"))
  {
    return execute_create(opt);
  }
  else if (!strcmp(command, "store"))
  {
    return execute_store(opt);
  }
  else
  {
    fprintf(stderr, "Unknown command: %s\n", command);
    return -1;
  }
}
