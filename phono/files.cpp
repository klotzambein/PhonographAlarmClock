#import "files.h"

#import "Arduino.h"
#import "Wire.h"
#import <EEPROM.h>
#import "text.h"

uint8_t to5bitChar(char c);
char toNormalChar(uint8_t c);
bool get_isPageFree(uint8_t page);
bool get_nxtPage(uint8_t page);
void get_5biChars(uint8_t *buffer, uint8_t page);
bool checkFile(char *addr, uint8_t page);
bool writePage(char *addr, uint8_t nxt, uint8_t page);

FilePages filePages[64];

int8_t findFile(char *addr)
{
    for (int i = 0; i < 64; i++)
    {
        if (filePages[i].cbaFre & 0x0001)
            continue;
        if (checkFile(addr, i))
            return i;
    }
    return -1;
}

void deleteFile(uint8_t page)
{
    while (true)
    {
        filePages[page].cbaFre &= 0x0001;
        uint8_t nxt = get_nxtPage(page);

        if (nxt == page)
        {
            saveFilePage(page);
            break;
        }

        filePages[page].kjNxt = (filePages[page].kjNxt & 0xFFC0) | page;
        saveFilePage(page);

        page = nxt;
    }
}

int8_t createFile(char *addr, uint16_t size)
{
    size >>= 8;
    int8_t freePages[size];
    for (int i = 0, j = 0; j < size; i++)
    {
        if (i >= 64)
            return -1;
        if (get_isPageFree(i))
            freePages[j++] = i;
    }
    for (int i = 0; i < size - 1; i++)
    {
        if (writePage(addr, freePages[i + 1], freePages[i]))
            addr = &TEXT_ZERO;
        else
            addr += 11;
        saveFilePage(freePages[i]);
    }
    writePage(addr, freePages[size - 1], freePages[size - 1]);
    saveFilePage(freePages[size - 1]);
}

int sprintFileAddress(char *str, uint8_t page, uint8_t maxLength)
{
    uint8_t buffer[11];
    get_5biChars(&buffer[0], page);

    int maxI = (maxLength < 11) ? maxLength : 11;
    for (int i = 0; i < maxI; i++)
        *str++ = toNormalChar(buffer[i]);

    uint8_t nxt = get_nxtPage(page);
    if (nxt == page)
        return 12;
    return sprintFileAddress(str, nxt, maxLength - 12);
}

void saveFilePages()
{
    EEPROM.put(FILE_PAGES_EEPROM_ADDRESS, filePages);
}
void saveFilePage(uint8_t page)
{
    EEPROM.put(FILE_PAGES_EEPROM_ADDRESS + page * 8, filePages[page]);
}

void loadFilePages()
{
    EEPROM.get(FILE_PAGES_EEPROM_ADDRESS, filePages);
}

//------------------------------------

bool checkFile(char *addr, uint8_t page)
{
    uint8_t buffer[11];
    get_5biChars(&buffer[0], page);

    for (int i = 0; i < 11; i++)
    {
        if (*(addr + i) != to5bitChar(buffer[i]))
            return false;
        if (buffer[i] == 0)
            return true;
    }

    uint8_t nxt = get_nxtPage(page);
    if (nxt == page)
        return *(addr + 12) == 0;
    return checkFile(addr + 11, nxt);
}

bool writePage(char *addr, uint8_t nxt, uint8_t page)
{
    uint8_t b[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    for (; i < 11 && addr[i] != 0; i++)
        b[i] = to5bitChar(addr[i]);

    filePages[page].cbaFre = b[0] << 1 & b[1] << 6 & b[2] << 11 & 0x0001;
    filePages[page].fed = b[3] << 1 & b[4] << 6 & b[5] << 11;
    filePages[page].ihg = b[6] << 1 & b[7] << 6 & b[8] << 11;
    filePages[page].kjNxt = b[9] << 6 & b[10] << 11 & nxt;

    return i < 11;
}

bool get_isPageFree(uint8_t page)
{
    return filePages[page].cbaFre & 0x0001;
}
bool get_nxtPage(uint8_t page)
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

uint8_t to5bitChar(char c)
{
    switch (c)
    {
    case 'a':
    case 'A':
        return 1;
    case 'b':
    case 'B':
        return 2;
    case 'c':
    case 'C':
        return 3;
    case 'd':
    case 'D':
        return 4;
    case 'e':
    case 'E':
        return 5;
    case 'f':
    case 'F':
        return 6;
    case 'g':
    case 'G':
        return 7;
    case 'h':
    case 'H':
        return 8;
    case 'i':
    case 'I':
        return 9;
    case 'j':
    case 'J':
        return 10;
    case 'k':
    case 'K':
        return 11;
    case 'l':
    case 'L':
        return 12;
    case 'm':
    case 'M':
        return 13;
    case 'n':
    case 'N':
        return 14;
    case 'o':
    case 'O':
        return 15;
    case 'p':
    case 'P':
        return 16;
    case 'q':
    case 'Q':
        return 17;
    case 'r':
    case 'R':
        return 18;
    case 's':
    case 'S':
        return 19;
    case 't':
    case 'T':
        return 20;
    case 'u':
    case 'U':
        return 21;
    case 'v':
    case 'V':
        return 22;
    case 'w':
    case 'W':
        return 23;
    case 'x':
    case 'X':
    default:
        return 24;
    case 'y':
    case 'Y':
        return 25;
    case 'z':
    case 'Z':
        return 26;
    case '/':
        return 27;
    case 0:
        return 0;
    }
}
char toNormalChar(uint8_t c)
{
    switch (c)
    {
    case 1:
        return 'a';
    case 2:
        return 'b';
    case 3:
        return 'c';
    case 4:
        return 'd';
    case 5:
        return 'e';
    case 6:
        return 'f';
    case 7:
        return 'g';
    case 8:
        return 'h';
    case 9:
        return 'i';
    case 10:
        return 'j';
    case 11:
        return 'k';
    case 12:
        return 'l';
    case 13:
        return 'm';
    case 14:
        return 'n';
    case 15:
        return 'o';
    case 16:
        return 'p';
    case 17:
        return 'q';
    case 18:
        return 'r';
    case 19:
        return 's';
    case 20:
        return 't';
    case 21:
        return 'u';
    case 22:
        return 'v';
    case 23:
        return 'w';
    case 24:
    default:
        return 'x';
    case 25:
        return 'y';
    case 26:
        return 'z';
    case 27:
        return '/';
    case 0:
        return 0;
    }
}
