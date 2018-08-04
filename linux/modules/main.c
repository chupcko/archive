#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
  void *handle;
  int (*cosine)(void);
  char *error;
  handle = dlopen ("/home/chupcko/qqq/moduo.so", RTLD_LAZY);
  if (!handle)
  {
    fputs (dlerror(), stderr);
    exit(1);
  }
  cosine = (int (*)(void))dlsym(handle, "mount");
  if ((error = (char *)dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }
  printf ("%d\n", (*cosine)());
  dlclose(handle);
  return 0;
}
