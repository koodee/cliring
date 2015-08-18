#include "main.h"

void help()
{
  fprintf(stderr, "TODO\n");
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
  s_option *opt = malloc(sizeof(s_option));
  init_options(opt);

  while ((c = getopt(argc, argv, "a:k:p:n:")) != -1)
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
