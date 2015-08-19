#include "commands.h"

int execute_lock(s_option *opt)
{
  if (!opt->keyring)
  {
    opt->keyring = get_default_keyring();
  }

  return keyring_lock(opt->keyring);
}

int execute_get(s_option *opt)
{
  if (!opt->keyring)
  {
    opt->keyring = get_default_keyring();
  }
  else if (!opt->attributes_count)
  {
    fprintf(stderr, "Please provide attributes to search for.\n");
    return 1;
  }

  return search(opt->keyring, opt->attributes);
}

int execute_create(const s_option *opt)
{
  if (!opt->keyring)
  {
    fprintf(stderr, "You must provide a name for the new keyring.\n");
    return 1;
  }
  else
  {
    char *password = try_secure_alloc(sizeof(char) * PASSWORD_MAX_SIZE);

    if (opt->password)
      password = strncpy(password, opt->password, PASSWORD_MAX_SIZE);
    else
      read_password(&password);

    int result = keyring_create(opt->keyring, password);

    free_password(password);
    return result;
  }
}

int execute_list(const s_option *opt)
{
  return keyrings_list();
}

int execute_store(s_option *opt)
{
  if (!opt->keyring)
  {
    opt->keyring = get_default_keyring();
  }

  if (!opt->display_name)
  {
    fprintf(stderr, "You must provide a display name for the password\n");
    return 1;
  }

  char *password = try_secure_alloc(sizeof(char) * PASSWORD_MAX_SIZE);

  if (opt->password)
    password = strncpy(password, opt->password, PASSWORD_MAX_SIZE);
  else
    read_password(&password);

  int result =  password_store(opt->keyring, password, opt->display_name, opt->attributes);

  free_password(password);
  return result;
}
