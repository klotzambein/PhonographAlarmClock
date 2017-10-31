#ifndef FILES_H
#define FILES_H

#import "Arduino.h"

#define FILE_STORAGE_ADDRESS 0x68
#define FILE_PAGES_EEPROM_ADDRESS 512

typedef uint16_t int5551_t;
typedef uint16_t int556_t;
extern struct FilePages
{
    int5551_t cbaFre;
    int5551_t fed;
    int5551_t ihg;
    int556_t kjNxt;
} filePages[64];


int findFile(char *addr);
void deleteFile(uint8_t page);
void saveFilePages();
void loadFilePages();
int sprintFileAddress(char *str, uint8_t page, uint8_t maxLength);

#endif