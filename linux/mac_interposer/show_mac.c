#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  int fd;
  struct ifreq ifr;
  int i;

  fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  strcpy(ifr.ifr_name, "eth0");
  ioctl(fd, SIOCGIFHWADDR, &ifr);
  printf("%s %d ", ifr.ifr_name, ifr.ifr_hwaddr.sa_family);
  for(i = 0; i < 14; i++)
    printf("%02x ", (unsigned char)ifr.ifr_hwaddr.sa_data[i]);
  printf("\n");
  close(fd);
  return 0;
}
