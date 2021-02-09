#pragma once
char * mktemp(char *template);
int chdir (const char *__path);
int close (int __fildes);
int execl (const char *__path, const char *, ...);
int execle (const char *__path, const char *, ...);
int execlp (const char *__file, const char *, ...);
int     isatty (int __fildes);
