#import "files.h"

uint8_t to5bitChar(char c);
uint8_t compareChars(int5551_t char5bit, char a, char b, char c);
inline bool checkPage(char *addr, uint8_t page);

int findFile(char *addr)
{
    for (int i = 0; i < 64; i++)
    {
        if (filePages[i].cbaFre & 0x0001)
            continue;
        if (checkPage(addr, i))
            return i;
    }
    return -1;
}

bool checkPage(char *addr, uint8_t page)
{
    uint8_t x = compareChars(filePages[page].cbaFre & 0xFFFE, *addr, *(addr + 1), *(addr + 2));
    if (x != 1)
        return x;
    uint8_t y = compareChars(filePages[page].fed & 0xFFFE, *(addr + 3), *(addr + 4), *(addr + 5));
    if (y != 1)
        return y;
    uint8_t z = compareChars(filePages[page].ihg & 0xFFFE, *(addr + 6), *(addr + 7), *(addr + 8));
    if (z != 1)
        return z;
    uint8_t w = compareChars(filePages[page].kjNxt & 0xFFC0, *(addr + 9), *(addr + 10), 0);
    if (w == 3) // Complete match
        return true;

    uint8_t nxt = filePages[page].kjNxt & 0x3F;
    if (nxt == page)
        return false;
    return checkPage(addr + 11, nxt);
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
