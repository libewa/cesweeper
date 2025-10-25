#include "keypad.h"
#include <ti/getcsc.h>

char getKeypadInput(void) {
    uint8_t key = os_GetCSC();
    switch (key) {
        case sk_Del:
            return '\b'; // Backspace
        case sk_Math:
            return 'A';
        case sk_Apps:
            return 'B';
        case sk_Prgm:
            return 'C';
        case sk_Recip:
            return 'D';
        case sk_Sin:
            return 'E';
        case sk_Cos:
            return 'F';
        case sk_Tan:
            return 'G';
        case sk_Power:
            return 'H';
        case sk_Square:
            return 'I';
        case sk_Comma:
            return 'J';
        case sk_LParen:
            return 'K';
        case sk_RParen:
            return 'L';
        case sk_Div:
            return 'M';
        case sk_Log:
            return 'N';
        case sk_7:
            return 'O';
        case sk_8:
            return 'P';
        case sk_9:
            return 'Q';
        case sk_Mul:
            return 'R';
        case sk_Ln:
            return 'S';
        case sk_4:
            return 'T';
        case sk_5:
            return 'U';
        case sk_6:
            return 'V';
        case sk_Sub:
            return 'W';
        case sk_Store:
            return 'X';
        case sk_1:
            return 'Y';
        case sk_2:
            return 'Z';
        case sk_Enter:
            return '\n';
        case sk_0:
            return ' ';
        default:
            return '\0';
    }
}
