#ifndef __MAIN__H__
#define __MAIN__H__

#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_CHILD_DATA_SIZE 4
#define DEFAULT_JOB_FILE_NAME   "-"

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

#define MAX_COMMAND_SIZE 8192
typedef char command_t[MAX_COMMAND_SIZE+1];

typedef struct child_data_t
{
  boolean_t used;
  pid_t pid;
  command_t command;
} child_data_t;

typedef struct job_data_t
{
  int size;
  child_data_t* children_data;
  FILE* file;
} job_data_t;

#define DEBUG(format, ...)                                 \
do                                                         \
{                                                          \
  if(Debug == TRUE)                                        \
    fprintf(stderr, "Debug: " format "\n", ##__VA_ARGS__); \
}                                                          \
while(FALSE)                                               \

#define ERROR(format, ...)                               \
do                                                       \
{                                                        \
  fprintf(stderr, "Error: " format "\n", ##__VA_ARGS__); \
  exit(EXIT_FAILURE);                                    \
}                                                        \
while(FALSE)                                             \

#undef _EXTERN_
#undef _INIT_
#ifdef __MAIN__C__
  #define _EXTERN_
  #define _INIT_(...) = __VA_ARGS__
#else
  #define _EXTERN_ extern
  #define _INIT_(...)
#endif

#include "variable.h"
#include "prototype.h"

#endif
