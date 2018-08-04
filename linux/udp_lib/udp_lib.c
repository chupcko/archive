#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "udp_lib.h"

int udp_send(char *server, int port, char *string, int length)
{
  int socket_descriptor;
  struct sockaddr_in server_address;

  if((socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    return 10;
  bzero(&server_address, (size_t)sizeof(struct sockaddr_in));
  server_address.sin_family = PF_INET;
  if(inet_pton(PF_INET, server, (void *)&server_address.sin_addr) <= 0)
  {
    close(socket_descriptor);
    return 11;
  }
  server_address.sin_port = htons((uint16_t)port);
  if(sendto(socket_descriptor, string, length, 0, (struct sockaddr *)&server_address, (socklen_t)sizeof(struct sockaddr_in)) < 0)
  {
    close(socket_descriptor);
    return 12;
  }
  close(socket_descriptor);
  return 0;
}

int udp_recv(int port, char *client, char *string, int *length, int max_length, int timeout)
{
  int socket_descriptor;
  struct sockaddr_in server_address;
  struct pollfd poll_fd;
  int poll_return;

  if((socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    return 10;
  bzero(&server_address, (size_t)sizeof(struct sockaddr_in));
  server_address.sin_family = PF_INET;
  server_address.sin_addr.s_addr = htonl((uint32_t)INADDR_ANY);
  server_address.sin_port = htons((uint16_t)port);
  if(bind(socket_descriptor, (struct sockaddr *)&server_address, (socklen_t)sizeof(struct sockaddr_in)) < 0)
  {
    close(socket_descriptor);
    return 11;
  }
  poll_fd.fd = socket_descriptor;
  poll_fd.events = POLLIN;
  poll_fd.revents = 0;
  poll_return = poll(&poll_fd, 1, timeout);
  if(poll_return < 0)
  {
    close(socket_descriptor);
    return 12;
  }
  else if(poll_return == 0)
  {
    close(socket_descriptor);
    return 1;
  }
  else
  {
    struct sockaddr_in client_address;
    socklen_t client_address_length;
    ssize_t recv_length;

    bzero(&client_address, (size_t)sizeof(struct sockaddr_in));
    client_address_length = (socklen_t)sizeof(struct sockaddr_in);
    if((recv_length = recvfrom(socket_descriptor, (void *)string, (size_t)max_length, 0, (struct sockaddr *)&client_address, &client_address_length)) < 0)
    {
      close(socket_descriptor);
      return 13;
    }
    *length = recv_length;
    if(client != NULL)
      if(inet_ntop(PF_INET, (void *)&(client_address.sin_addr), client, udp_client_length) == NULL)
      {
        close(socket_descriptor);
        return 14;
      }
  }
  close(socket_descriptor);
  return 0;
}
