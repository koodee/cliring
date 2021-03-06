#include "main.h"

char *prg_name = "";

void help()
{
  fprintf(stderr, "Usage: %s command [OPTIONS]...\n", prg_name);
  fprintf(stderr, "Commands:\n");
  fprintf(stderr, "\tlist                                         Display a list of the existing keyrings\n");
  fprintf(stderr, "\tcreate -k keyring                            Create a new keyring.\n");
  fprintf(stderr, "\tdelete -k keyring                            Delete a keyring\n");
  fprintf(stderr, "\tstore [-k keyring] -n name -a attributes...  Store a password in a keyring\n");
  fprintf(stderr, "\tget [-k keyring] -a key:value...             Retrieve a password from a keyring that matches the key/value couples.\n");
  fprintf(stderr, "\tlock [-k keyring]                            Lock a keyring. If no keyring is provided, default keyring is locked\n");
  fprintf(stderr, "\tunlock [-k keyring]                          Unlock a keyring. If no keyring is provided, the default keyring unlocked\n");

  fprintf(stderr, "\n");

  fprintf(stderr, "Options:\n");
  fprintf(stderr, "\t-a --attributes\tA couple used to identify a keyring item. Must be in the form key:value\n");
  fprintf(stderr, "\t-h --help\tPrint this help.\n");
  fprintf(stderr, "\t-k --keyring\tA keyring name. Represents the new name of the keyring in the create command, identifies the keyring we want to use otherwise.\n");
  fprintf(stderr, "\t-n --name\tThe display name of the keyring item. It can't be used to retrieve the password.\n");
}

int execute_command(const char *command, s_option *opt)
{
  if (!strcmp(command, "list"))
  {
    return execute_list(opt);
  }
  else if (!strcmp(command, "create"))
  {
    return execute_create(opt);
  }
  else if (!strcmp(command, "delete"))
  {
    return execute_delete(opt);
  }
  else if (!strcmp(command, "store"))
  {
    return execute_store(opt);
  }
  else if (!strcmp(command, "get"))
  {
    return execute_get(opt);
  }
  else if (!strcmp(command, "lock"))
  {
    return execute_lock(opt);
  }
  else if (!strcmp(command, "unlock"))
  {
    return execute_unlock(opt);
  }
  else
  {
    fprintf(stderr, "Unknown command: %s\n", command);
    help();
    return -1;
  }
}

int get_attribute(const char *optarg, s_option *opt)
{
  int size = strlen(optarg);
  char *arg = malloc(sizeof(char) * size + 1);
  strncpy(arg, optarg, size + 1);

  char *attr_name = strtok(arg, ":");
  char *attr_value = strtok(NULL, "");

  if (attr_value == NULL)
  {
    free(arg);
    return 1;
  }

  opt->attributes_count++;
  gnome_keyring_attribute_list_append_string(opt->attributes, attr_name, attr_value);
  free(arg);
  return 0;
}

int main(int argc, char* const argv[])
{
  int index;
  int c;
  int result = 0;
  prg_name = argv[0];

  g_set_application_name(prg_name);

  s_option *opt = malloc(sizeof(s_option));
  init_options(opt);

  static struct option long_options[] = {
        {"attributes",  required_argument, 0, 'a' },
        {"help",        no_argument,       0, 'h' },
        {"keyring",     required_argument, 0, 'k' },
        {"name",        required_argument, 0, 'n' },
        {0,             0,                 0,  0  }
    };

  while ((c = getopt_long(argc, argv, "a:k:n:h", long_options, NULL)) != -1)
    switch (c)
    {
      case 'a':
        if (get_attribute(optarg, opt))
        {
          fprintf(stderr, "Malformated attribute: %s\n", optarg);
          free_options(opt);
          return 1;
        }
        break;
      case 'h':
        help();
        free_options(opt);
        return 0;
        break;
      case 'k':
        opt->keyring = strdup(optarg);
        break;
      case 'n':
        opt->display_name = optarg;
        break;
      default:
        help();
        free_options(opt);
        return 1;
    }

    if (argc == optind)
    {
      fprintf(stderr, "No command found.\n");
      help();
      result = 1;
    }
    else if (argc - optind > 1)
    {
      fprintf(stderr, "Please provide only one command.\n");
      help();
      result =  1;
    }
    else
      result = execute_command(argv[optind], opt);

    free_options(opt);
    return result;
}
