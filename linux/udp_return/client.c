#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define PORT 5000

#define MESSAGE "zdravo"

#define MAX_MESSAGE_LENGTH 1024

int main(void)
{
  int socket_descriptor;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  socklen_t client_address_length;
  char message[MAX_MESSAGE_LENGTH+1];
  ssize_t length;

  if((socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    return 10;
  bzero(&server_address, (size_t)sizeof(struct sockaddr_in));
  server_address.sin_family = PF_INET;
  if(inet_pton(PF_INET, SERVER, (void *)&server_address.sin_addr) <= 0)
  {
    close(socket_descriptor);
    return 11;
  }
  server_address.sin_port = htons((uint16_t)PORT);
  if(sendto(socket_descriptor, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&server_address, (socklen_t)sizeof(struct sockaddr_in)) < 0)
  {
    close(socket_descriptor);
    return 12;
  }
  bzero(&client_address, (size_t)sizeof(struct sockaddr_in));
  client_address_length = (socklen_t)sizeof(struct sockaddr_in);
  if((length = recvfrom(socket_descriptor, (void *)message, (size_t)MAX_MESSAGE_LENGTH, 0, (struct sockaddr *)&client_address, &client_address_length)) < 0)
  {
    close(socket_descriptor);
    return 13;
  }
  message[length] = '\0';
  printf("%08lx %d ## %s\n",(long)ntohl(client_address.sin_addr.s_addr), (int)ntohs(client_address.sin_port), message);
  close(socket_descriptor);
  return 0;
}
