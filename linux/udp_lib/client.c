#include <stdio.h>
#include <string.h>

#include "udp_lib.h"

#define DATA "CHUPCKO"

int main(void)
{
  switch(udp_send("127.0.0.1", 5000, DATA, strlen(DATA)))
  {
    case 0:
      printf("ok\n");
      break;
    default:
      printf("Error\n");
  }
  return 0;
}
