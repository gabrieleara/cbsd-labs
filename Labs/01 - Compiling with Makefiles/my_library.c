#include <stdio.h>
#include <stdarg.h>

#include "my_library.h"

void errprintf(const char *my_format, ...)
{
    va_list args;
    va_start(args, my_format);
    vfprintf(stderr, my_format, args);
    va_end(args);
}
