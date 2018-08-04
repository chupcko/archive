#include <stdio.h>

#include "udp_lib.h"

#define MAX_LENGTH 100

int main(void)
{
  char client[udp_client_length];
  char data[MAX_LENGTH];
  int length;

  switch(udp_recv(5000, client, data, &length, MAX_LENGTH, 10000))
  {
    case 0:
      printf("%s %d \"%s\"\n", client, length, data);
      break;
    case 1:
      printf("Timeout\n");
      break;
    default:
      printf("Error\n");
  }
  return 0;
}
