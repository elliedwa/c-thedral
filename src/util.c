#include "util.h"
char *
obj_to_bin(char *dest, const void *object, size_t osize)
{
        const unsigned char *p = (const unsigned char *)object;
        p += osize;
        char *s = dest;
        while (osize-- > 0) {
                p--;
                unsigned i = CHAR_BIT;
                while (i-- > 0) {
                        *s++ = ((*p >> i) & 1) + '0';
                }
        }
        *s = '\0';
        return dest;
}

