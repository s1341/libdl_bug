#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <pthread.h>

void destroy_key (void *key)
{
  printf ("in destroy_key\n");
}

void shared_method()
{
  pthread_key_t key;

  printf ("in shared_method\n");
  pthread_key_create(&key, destroy_key);

  printf ("calling dlsym\n");
  dlsym (RTLD_NEXT, "pthread_create");
  printf ("done calling dlsym\n");

  pthread_key_delete (key);
}

