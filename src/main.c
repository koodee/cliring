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
  else
  {
    fprintf(stderr, "Unknown command: %s\n", command);
    help();
    return -1;
  }
}

int main(int argc, char* const argv[])
{
  int index;
  int c;
  int result = 0;
  s_option *opt = malloc(sizeof(s_option));
  init_options(opt);

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

    free(opt);
    return result;
}
