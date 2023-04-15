#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define SLEEP_MILLI_SECCONDS 100

char CC_cur[] = { '\e', '[', '?', '2', '5', 'l' };
char CC_home[] = { '\e', '[', 'H' };

struct winsize Win_size;
size_t Out_size;
char *Out;

void cur_set(void)
{
  write(STDOUT_FILENO, CC_cur, sizeof CC_cur);
}

void clean(int signum)
{
  CC_cur[sizeof(CC_cur)-1] = 'h';
  cur_set();
  exit(0);
}

int calc(int row, int col, int time)
{
  int n = 4;
  int d = Win_size.ws_col/12;
  int s = ((time/n)%2)*2-1;
  int t = (-s)*(time%n)+s*(n/2);
  if
  (
    row > Win_size.ws_row/3 &&
    row < 2*Win_size.ws_row/3 &&
    col+d > Win_size.ws_col/3 &&
    col+d < 2*Win_size.ws_col/3
  )
  {
    return(d-(n/2)+t);
  }
  return(d);
}

void display(int time)
{
  memset((void *)&Out[sizeof(CC_home)], ' ', Out_size-sizeof(CC_home));
  for(int row = 0; row < Win_size.ws_row; row++)
  {
    char *Base = &Out[sizeof(CC_home)+row*Win_size.ws_col];
    for(int col = 0; col < Win_size.ws_col; col++)
    {
      if(Base[col] == ' ')
      {
        int pos = col;
        char fill = 'a'+rand()%('z'-'a'+1);
        do
        {
          Base[pos] = fill;
          pos += calc(row, pos, time);
        }
        while(pos < Win_size.ws_col);
      }
    }
  }
  write(STDOUT_FILENO, Out, Out_size);
}

int main(void)
{
  signal(SIGINT, &clean);
  signal(SIGQUIT, &clean);

  cur_set();
  srand((unsigned int)time(NULL));

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &Win_size);
  Out_size = sizeof(CC_home)+Win_size.ws_row*Win_size.ws_col;
  Out = (char *)malloc(Out_size);
  if(Out == NULL)
  {
    return(1);
  }
  memcpy((void *)Out, (void *)CC_home, sizeof(CC_home));

  int time = 0;
  for(;;)
  {
    display(time);
    time++;
    usleep(SLEEP_MILLI_SECCONDS*1000);
  }

  return(0);
}
