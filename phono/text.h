#ifndef TEXT_H
#define TEXT_H

#import "Arduino.h"
#import "makro.h"

int sprintHex(char *str, uint8_t number);

inline int sprintString(char *str, char *srcStr, size_t size)
{
    memcpy(str, srcStr, size);
    return size;
}

#define WRITE2STR(...) VFUNC(WRITE2STR, __VA_ARGS__)
#define WRITE2STR1(a) \
    (*str++) = a;
#define WRITE2STR2(a, b) \
    (*str++) = a;        \
    (*str++) = b;
#define WRITE2STR3(a, b, c) \
    (*str++) = a;           \
    (*str++) = b;           \
    (*str++) = c;
#define WRITE2STR4(a, b, c, d) \
    (*str++) = a;              \
    (*str++) = b;              \
    (*str++) = c;              \
    (*str++) = d;
#define WRITE2STR5(a, b, c, d, e) \
    (*str++) = a;                 \
    (*str++) = b;                 \
    (*str++) = c;                 \
    (*str++) = d;                 \
    (*str++) = e;
#define WRITE2STR6(a, b, c, d, e, f) \
    (*str++) = a;                    \
    (*str++) = b;                    \
    (*str++) = c;                    \
    (*str++) = d;                    \
    (*str++) = e;                    \
    (*str++) = f;
#define WRITE2STR7(a, b, c, d, e, f, g) \
    (*str++) = a;                       \
    (*str++) = b;                       \
    (*str++) = c;                       \
    (*str++) = d;                       \
    (*str++) = e;                       \
    (*str++) = f;                       \
    (*str++) = g;
#define WRITE2STR8(a, b, c, d, e, f, g, h) \
    (*str++) = a;                          \
    (*str++) = b;                          \
    (*str++) = c;                          \
    (*str++) = d;                          \
    (*str++) = e;                          \
    (*str++) = f;                          \
    (*str++) = g;                          \
    (*str++) = h;

#endif