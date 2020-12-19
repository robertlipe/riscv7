// Most of these could be __builtin_memcpy or __builtin_strcpy or whatever
// but dead simple C implementations give us more flexibility if we want
// to change calling conventions or change to LLVM or ...

void bcopy(const void *src, void *dest, int len) {
  if (dest < src)
    {
      const char *firsts = (const char *) src;
      char *firstd = (char *) dest;
      while (len--)
	*firstd++ = *firsts++;
    }
  else
    {
      const char *lasts = (const char *)src + (len-1);
      char *lastd = (char *)dest + (len-1);
      while (len--)
        *lastd-- = *lasts--;
    }
}

void bzero(void *dest, int n) {
  for (char* p = dest; n--;) {
    *p++ = '\0';
  }
}

#if 0
int ipl = 0;
__attribute__( ( optimize( "O3" ) ) )
int foo0(int new) {
  int x = ipl;
  ipl = new;
  return x;
}
#endif

int
strlen(const char *str) {
	const char* s;
        for (s = str; *s; ++s)
                ;
        return (s - str);
}

char*
strcpy(char* dest, const char* src) {
  	char *ret = dest;
  	while ((*dest++ = *src++) != '\0');
  	return ret;
}

// Swap the stupid argument order
void memcpy(void *dest, const void *src, int len) {
  return bcopy(src, dest, len);
}
