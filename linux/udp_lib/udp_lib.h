int udp_send(char *server, int port, char *string, int length);
/*
input:
  server: servere name
  port: port nunber
  string: data for send
  length: data length

output:
  return value 0: OK
  return value >=10: error
*/

#define udp_client_length (16+1)
int udp_recv(int port, char *client, char *string, int *length, int max_length, int timeout);
/*
input:
  port: number
  client: pointer to char[udp_cleint_length] (for return)
  string: pointer to char[*length] (for return)
  length: pointer to int, size of string (for return)
  max_length: max size of string
  timeout: timeout for blocking (in milliseconds)
output:
  return value 0: OK
    client: filled with client ip (if client != NULL)
    server: filled with data
    length: filled with data length
  return value 1: timeout
  return value >=10: error
*/
