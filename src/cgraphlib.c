#include "cgraphlib.h"
#include "cgraphlib-other.h"

void WW(FILE* file, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  int size = vsnprintf(NULL, 0, format, args);
  va_end(args);
  char* ret = malloc(sizeof(char) * (size + 1));
  va_start(args, format);
  vsnprintf(ret, size, format, args);
  ret[size] = '\0';
  fwrite(ret, size, 1, file);
  free(ret);
  return;
}

uint8_t getRandByte(void)
{
  return rand();
}