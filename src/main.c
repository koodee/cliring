#include "main.h"

char *prg_name = "";

void help()
{
  fprintf(stderr, "Usage: %s command [OPTIONS]...\n", prg_name);
  fprintf(stderr, "Commands:\n");
  fprintf(stderr, "\tlist\tDisplay a list of the existing keyrings\n");
  fprintf(stderr, "\tcreate -k keyring [-p password]\tCreate a new keyring.\n");
  fprintf(stderr, "\tstore -k keyring -n name [-p password] -a attributes...\tStore a password in a keyring\n");
  fprintf(stderr, "\tget -k keyring -a key:value...\tRetrieve a password from a keyring that matches the key/value couples.\n");

  fprintf(stderr, "\n");

  fprintf(stderr, "Options:\n");
  fprintf(stderr, "\t-a --attributes\tA couple used to identify a keyring item. Must be in the form key:value\n");
  fprintf(stderr, "\t-k --keyring\tA keyring name. Represents the new name of the keyring in the create command, identifies the keyring we want to use otherwise.\n");
  fprintf(stderr, "\t-n --name\tThe display name of the keyring item. It can't be used to retrieve the password.\n");
  fprintf(stderr, "\t-p --password\tOnly used when creating a new keyring or item. If not provided, the user will be prompted for the password.\n");
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
  else if (!strcmp(command, "get"))
  {
    return execute_get(opt);
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

  s_option *opt = malloc(sizeof(s_option));
  init_options(opt);

  static struct option long_options[] = {
        {"attributes",  required_argument, 0, 'a' },
        {"keyring",     required_argument, 0, 'k' },
        {"name",        required_argument, 0, 'n' },
        {"password",    required_argument, 0, 'p' },
        {0,             0,                 0,  0  }
    };

  while ((c = getopt_long(argc, argv, "a:k:n:p:", long_options, NULL)) != -1)
    switch (c)
    {
      case 'a':
        if (get_attribute(optarg, opt))
          fprintf(stderr, "Malformated attribute: %s\n", optarg);
          break;
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
        help();
        free(opt);
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

    gnome_keyring_attribute_list_free(opt->attributes);
    free(opt);
    return result;
}
