#ifndef FILES_H
#define FILES_H

#import "Arduino.h"
#import "Wire.h"

#define FILES_ADDRESS 0x68

typedef uint16_t int5551_t;
typedef uint16_t int556_t;
struct
{
    int5551_t cbaFre;
    int5551_t fed;
    int5551_t ihg;
    int556_t kjNxt;
} filePages[64];

int findFile(char *addr);
void save();
void load();

#endif