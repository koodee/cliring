#include "main.h"

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
        result = 1;
    }

    if (result == 0 && argc == optind)
    {
      fprintf(stderr, "No command found.\n");
      // Call help function
      result = 1;
    }
    else if (argc - optind > 1)
    {
      fprintf(stderr, "Please provide only one command.\n");
      // Call help function
      result =  1;
    }
    else
      result = execute_command(argv[optind], opt);

    free(opt);
    return result;
}
