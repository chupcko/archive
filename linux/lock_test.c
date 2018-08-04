#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME "lock_test"

typedef int lock_t;

typedef struct data_t
{
  lock_t lock;
  int    data;
} data_t;

void error(char* format, ...)
{
  va_list arguments;

  va_start(arguments, format);
  vfprintf(stderr, format, arguments);
  va_end(arguments);
  fputc('\n', stderr);
  exit(EXIT_FAILURE);
}

void do_lock(volatile lock_t* lock)
{
  while(__sync_lock_test_and_set(lock, 1) != 0)
    while(*lock != 0);
}

void do_unlock(volatile lock_t* lock)
{
  __sync_lock_release(lock);
}

data_t* create_data(void)
{
  int shared_memory_fd;
  void* shared_memory;

  shm_unlink(NAME);
  shared_memory_fd = shm_open(NAME, O_CREAT|O_RDWR, S_IREAD|S_IWRITE);
  if(shared_memory_fd == -1)
    error("Cannot shm_open(%d %s)", errno, strerror(errno));
  if(ftruncate(shared_memory_fd, sizeof(data_t)) == -1)
    error("Cannot ftruncate(%d %s)", errno, strerror(errno));
  shared_memory = mmap(NULL, sizeof(data_t), PROT_READ|PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
  if(shared_memory == MAP_FAILED)
    error("Cannot shmat(%d %s)", errno, strerror(errno));
  return (data_t*)shared_memory;
}

data_t* open_data(void)
{
  int shared_memory_fd;
  void* shared_memory;

  shared_memory_fd = shm_open(NAME, O_RDWR, S_IREAD|S_IWRITE);
  if(shared_memory_fd == -1)
    error("Cannot shm_open(%d %s)", errno, strerror(errno));
  shared_memory = mmap(NULL, sizeof(data_t), PROT_READ|PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
  if(shared_memory == MAP_FAILED)
    error("Cannot shmat(%d %s)", errno, strerror(errno));
  return (data_t*)shared_memory;
}

void init(data_t* data)
{
  data->lock = 0;
  data->data = 0;
}

void master()
{
  data_t* data = create_data();
  init(data);

  for(;;)
  {
    do_lock(&data->lock);
    printf("master: %d\n", data->data);
    sleep(1);
    do_unlock(&data->lock);
    sleep(1);
  }
}

void slave()
{
  data_t* data = open_data();

  for(;;)
  {
    do_lock(&data->lock);
    printf("slave: %d\n", data->data);
    data->data++;
    do_unlock(&data->lock);
    sleep(2);
  }
}

int main(int arguments_number, char* arguments_value[])
{
  if(arguments_number == 2)
    switch(arguments_value[1][0])
    {
      case 'm':
        master();
        break;
      case 's':
        slave();
        break;
    }
  return EXIT_SUCCESS;
}
