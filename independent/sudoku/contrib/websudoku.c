/*

curl -s 'http://play.websudoku.com/?level=3' | grep CLASS=s0 | ./websudoku > level3.sdk

*/

#include <stdio.h>

void print(char character, int count)
{
  printf("%c", character);
  if(count%9 == 8)
    printf("\n");
}

int main(void)
{
  char character;
  int count;
  int state;

  count = 0;
  state = 0;
  while((character = getchar()) != EOF)
    switch(state)
    {
      case 0:
        if(character == 'S')
          state = 1;
        break;
      case 1:
        if(character == '=')
          state = 2;
        else if(character != 'S')
          state = 0;
        break;
      case 2:
        if(character == 'd')
        {
          print('.', count++);
          state = 0;
        }
        else if(character == 's')
          state = 10;
        else
          state = 0;
        break;
      case 10:
        if(character == '=')
          state = 11;
        break;
      case 11:
        if(character == '\"')
          state = 12;
        else
          state = 10;
        break;
      case 12:
        print(character, count++);
        state = 0;
        break;
    }
  return 0;
}
