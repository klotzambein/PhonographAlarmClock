#import "files.h"

#import "Arduino.h"
#import "Wire.h"
#import <EEPROM.h>
#import "text.h"

uint8_t to5bitChar(char c);
uint8_t compareChars(int5551_t char5bit, char a, char b, char c);
inline bool checkPage(char *addr, uint8_t page);

FilePages filePages[64];

int findFile(char *addr)
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

bool checkFile(char *addr, uint8_t page)
{
    uint8_t buffer[11];
    get_5biChars(&buffer[0], page);

    for (int i = 0; i < 11; i++)
    {
        if (*(addr + i) == 0 && buffer[i] == 0)
            return true;
        if ()
    }

    uint8_t x = compareChars(filePages[page].cbaFre, *addr, *(addr + 1), *(addr + 2));
    if (x != 1)
        return x;
    uint8_t y = compareChars(filePages[page].fed, *(addr + 3), *(addr + 4), *(addr + 5));
    if (y != 1)
        return y;
    uint8_t z = compareChars(filePages[page].ihg, *(addr + 6), *(addr + 7), *(addr + 8));
    if (z != 1)
        return z;
    uint8_t w = compareChars(filePages[page].kjNxt & 0xFFC0, *(addr + 9), *(addr + 10), 0);
    if (w == 3) // Complete match
        return true;

    uint8_t nxt = get_nxtPage(page);
    if (nxt == page)
        return false;
    return checkFile(addr + 11, nxt);
}

uint8_t compareChars(int5551_t char5bit, char a, char b, char c)
{
    if (to5bitChar(a) == (char5bit >> 1 & 0x1F))
    {
        if (a == 0)
            return 2;
        if (to5bitChar(b) == (char5bit >> 6 & 0x1F))
        {
            if (b == 0)
                return 3;
            if (to5bitChar(c) == (char5bit >> 11 & 0x1F))
            {
                if (c == 0)
                    return 4;
                return 1;
            }
        }
    }
    return 0;
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

void deleteFile(uint8_t page)
{
    uint8_t nxt;
    while (true)
    {
        filePages[page].cbaFre &= 0x0001;
        nxt = get_nxtPage(page);
        if (nxt == page)
            break;
        filePages[page].kjNxt = (filePages[page].kjNxt & 0xFFC0) | page;
        page = nxt;
    }
    saveFilePages();
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

void loadFilePages()
{
    EEPROM.get(FILE_PAGES_EEPROM_ADDRESS, filePages);
}