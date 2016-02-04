#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>

extern void * __libc_dlopen_mode(char *name, int flags);
extern void * __libc_dlsym(void *handle, char *name);
extern void __libc_dlclose(void *handle);

int stopping = 0;
int stopped = 0;

void * threadfunc (void * arg)
{
  printf ("in threadfunc\n");

  void * handle = __libc_dlopen_mode ("./test_unload.so",  RTLD_LAZY | 0x80000000);
  printf ("dlopen ok handle: %p\n", handle);

  void (*pfn_shared_method)(void) = __libc_dlsym(handle, "shared_method");

  printf ("before func\n");
  pfn_shared_method ();
  printf ("after func\n");

  printf ("about to dlclose handle: %p\n", handle);
  __libc_dlclose (handle);
  printf ("done dlclose\n");

  while (!stopping)
      sleep (1);

  printf ("leaving threadfunc\n");
  stopped = 1;
}

int main (int argc, char **argv)
{
  printf ("started\n");

  pthread_t thread;

  pthread_create (&thread, NULL, threadfunc, NULL);

  printf ("letting thread run...\n");
  sleep (5);
  printf ("stopping thread...\n");
  stopping = 1;

  while(!stopped)
    sleep(1);
  return 0;
}

