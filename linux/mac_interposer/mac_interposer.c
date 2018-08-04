#define _SYS_IOCTL_H
#include <bits/ioctls.h>
#include <net/if.h>
#include <stdio.h>
#include <dlfcn.h>

#define NEW_ADDRESS { 0x00, 0xd0, 0xc9, 0x95, 0x55, 0x83 }

#define RTLD_NEXT ((void *)-1l)

int ioctl(unsigned int fd, unsigned int cmd, unsigned long arg)
{
  int return_value;

  static int (*func)(int, int, unsigned long) = NULL;
  if(func == NULL)
    func = (int(*)(int, int, unsigned long))dlsym(RTLD_NEXT, "ioctl");
  return_value = func(fd, cmd, arg);
  if(cmd == SIOCGIFHWADDR)
  {
    struct ifreq *ifr;
    int i;
    char address[6] = NEW_ADDRESS;

    ifr = (struct ifreq *)arg;
    for(i = 0; i < sizeof address; i++)
      ifr->ifr_hwaddr.sa_data[i] = address[i];
  }
  return return_value;
}
