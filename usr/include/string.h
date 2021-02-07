// Not present in UNIXv7. long unsigned int deferred to size_t from ISO c89. RJL

#include <stddef.h>

void *   memchr (const void *, int, long unsigned int);
int      memcmp (const void *, const void *, long unsigned int);
void *   memcpy (void *__restrict, const void *__restrict, long unsigned int);
void *   memmove (void *, const void *, long unsigned int);
void *   memset (void *, int, long unsigned int);
char    *strcat (char *__restrict, const char *__restrict);
char    *strchr (const char *, int);
int      strcmp (const char *, const char *);
int      strcoll (const char *, const char *);
char    *strcpy (char *__restrict, const char *__restrict);
long unsigned int   strcspn (const char *, const char *);
char    *strerror (int);
size_t strlen (const char *);
char    *strncat (char *__restrict, const char *__restrict, long unsigned int);
int      strncmp (const char *, const char *, long unsigned int);
char    *strncpy (char *__restrict, const char *__restrict, long unsigned int);
char    *strpbrk (const char *, const char *);
char    *strrchr (const char *, int);
long unsigned int   strspn (const char *, const char *);
char    *strstr (const char *, const char *);
