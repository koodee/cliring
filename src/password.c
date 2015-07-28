#include "password.h"

const int PASSWORD_MAX_SIZE = 64;


// Code from http://stackoverflow.com/questions/1196418/getting-a-password-in-c-without-using-getpass-3
int read_password(char **password)
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

    printf("Keyring password: ");
    fgets(*password, PASSWORD_MAX_SIZE, stdin);
    (*password)[strlen(*password) - 1] = 0;

    /* restore terminal */
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        return 1;
    }

    return 0;
}
