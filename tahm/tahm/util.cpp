#include <stdlib.h>
#include <stdint.h>
#include <string.h>

bool compareStrings(const char* str1, const char* str2) 
{
    size_t a = strlen(str1), b = strlen(str2);
    if (a != b) return false;
    return (strncmp(str1, str2, a) == 0);
}