#include "main.h"

int execute_create(const s_option *opt)
{
  char *password = NULL;

  if (!opt->keyring)
  {
    fprintf(stderr, "You must provide a name for the new keyring.\n");
    return 1;
  }
  else
  {
    if (opt->password)
      password = opt->password;
    else
    {
      password = malloc(sizeof(char) * PASSWORD_MAX_SIZE);
      read_password(&password);
    }

    return keyring_create(opt->keyring, password);
  }
}

int execute_list(const s_option *opt)
{
  return keyrings_list();
}

int execute_store(const s_option *opt)
{
  char *password = NULL;

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
  if (!opt->password)
  {
    password = malloc(sizeof(char) * PASSWORD_MAX_SIZE);
    read_password(&password);
  }
  else
    password = opt->password;

  //return password_store(opt->keyring, password, opt->display_name);
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

int main(int argc, char* const argv[])
{
  int index;
  int c;
  s_option *opt = malloc(sizeof(s_option));

  while ((c = getopt(argc, argv, "k:p:n:")) != -1)
    switch (c)
    {
      case 'k':
        opt->keyring = optarg;
        break;
      case 'n':
        opt->display_name = optarg;
        break;
      case 'p':
        opt->password = optarg;
        break;
      default:
        return 1;
    }

    if (argc == optind)
    {
      fprintf(stderr, "No command found.\n");
      // Call help function
      return 1;
    }
    else if (argc - optind > 1)
    {
      fprintf(stderr, "Please provide only one command.\n");
      // Call help function
      return 1;
    }
    else
    {
      return execute_command(argv[optind], opt);
    }

  return 0;
}
