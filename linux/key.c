#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
  struct termios t;
  #define SIZE 16
  char a[SIZE];

  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  t.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  while(true)
  {
    int r = read(STDIN_FILENO, a, SIZE-1);
    a[r] = '\0';
    for(int i = 0; i < r; i++)
    {
      printf("%02x", a[i]);
    }
    printf("\n");
  }
  return 0;
}
