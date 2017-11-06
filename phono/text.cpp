#import "text.h"

const char TEXT_ZERO = 0;

char ToHex(uint8_t number)
{
    switch (number & 0x0F)
    {
    case 0x0:
        return '0';
    case 0x1:
        return '1';
    case 0x2:
        return '2';
    case 0x3:
        return '3';
    case 0x4:
        return '4';
    case 0x5:
        return '5';
    case 0x6:
        return '6';
    case 0x7:
        return '7';
    case 0x8:
        return '8';
    case 0x9:
        return '9';
    case 0xA:
        return 'A';
    case 0xB:
        return 'B';
    case 0xC:
        return 'C';
    case 0xD:
        return 'D';
    case 0xE:
        return 'E';
    case 0xF:
        return 'F';
    }
}

int sprintHex(char *str, uint8_t number)
{
    WRITE2STR(ToHex(number >> 4), ToHex(number))
    return 2;
}

int sprintJsonString(char *str, char *name, int nameSize, char *content, int contentSize)
{
    WRITE2STR('"')
    str += sprintString(str, name, nameSize);
    WRITE2STR('"', ':', '"')
    str += sprintString(str, content, contentSize);
    WRITE2STR('"', ';')
    return 6 + nameSize + contentSize;
}