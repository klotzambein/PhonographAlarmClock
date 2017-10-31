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


inline bool get_isPageFree(uint8_t page)
{
    return filePages[page].cbaFre & 0x0001;
}
inline bool get_nxtPage(uint8_t page)
{
    return filePages[page].kjNxt & 0x003F;
}
void get_5biChars(uint8_t *buffer, uint8_t page)
{
    buffer[0] = filePages[page].cbaFre >> 1 & 0x1F;
    buffer[1] = filePages[page].cbaFre >> 6 & 0x1F;
    buffer[2] = filePages[page].cbaFre >> 11 & 0x1F;
    buffer[3] = filePages[page].fed >> 1 & 0x1F;
    buffer[4] = filePages[page].fed >> 6 & 0x1F;
    buffer[5] = filePages[page].fed >> 11 & 0x1F;
    buffer[6] = filePages[page].ihg >> 1 & 0x1F;
    buffer[7] = filePages[page].ihg >> 6 & 0x1F;
    buffer[8] = filePages[page].ihg >> 11 & 0x1F;
    buffer[9] = filePages[page].kjNxt >> 1 & 0x1F;
    buffer[10] = filePages[page].kjNxt >> 6 & 0x1F;
}

int findFile(char *addr);
void deleteFile(uint8_t page);
void saveFilePages();
void loadFilePages();

#endif