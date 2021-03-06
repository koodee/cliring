#include "commands.h"

int execute_delete(s_option *opt)
{
  if (!opt->keyring)
  {
    fprintf(stderr, "Please provide the keyring you want to delete.\n");
    return 1;
  }

  return keyring_delete(opt->keyring);
}

int execute_unlock(s_option *opt)
{
  if (!opt->keyring)
  {
    opt->keyring = get_default_keyring();
  }

  return keyring_unlock(opt->keyring);
}

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

  GnomeKeyringResult res = keyring_unlock(opt->keyring);

  if (res == GNOME_KEYRING_RESULT_OK)
    return search(opt->keyring, opt->attributes);
  else
    return res;
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

    read_password(&password, "Enter the new keyring password");

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

  GnomeKeyringResult res = keyring_unlock(opt->keyring);

  if (res != GNOME_KEYRING_RESULT_OK)
    return res;

  char *password = try_secure_alloc(sizeof(char) * PASSWORD_MAX_SIZE);

  read_password(&password, "Enter the password you want to store");

  int result = password_store(opt->keyring, password, opt->display_name, opt->attributes);

  free_password(password);
  return result;
}
