#ifndef KEY_MAP_H
#define KEY_MAP_H

//Resource: https://www.cs.umd.edu/~hollings/cs412/s98/project/proj1/index.html

#define ESC 27 /* ASCII escape */


/* Scancodes for shift and capslock keys: */

#define LSHIFT_PRESSED 0x2A  /* Scan codes for shift press, */
#define LSHIFT_RELEASED 0xAA /* shift release and capslock  */
#define RSHIFT_PRESSED 0x36  /* keys.                       */
#define RSHIFT_RELEASED 0xB6
#define CAPSLOCK 0x3A
#define CAPSLOCK_RELEASED 0xBA

#define CTRL 0x1D

#define F1 0x3B
#define F2 0x3C

#define BACKSPACE 8 /* Ascii codes for Backspace, Tab and enter */
#define TAB 9       /* keys.                                    */
#define ENTER_KEY 13

char scanToAscii[58][2] = /* Array containing ascii codes for
			       appropriate scan codes */
    {
        {0, 0},
        {ESC, ESC},
        {'1', '!'},
        {'2', '@'},
        {'3', '#'},
        {'4', '$'},
        {'5', '%'},
        {'6', '^'},
        {'7', '&'},
        {'8', '*'},
        {'9', '('},
        {'0', ')'},
        {'-', '_'},
        {'=', '+'},
        {8, 8},
        {9, 9},
        {'q', 'Q'},
        {'w', 'W'},
        {'e', 'E'},
        {'r', 'R'},
        {'t', 'T'},
        {'y', 'Y'},
        {'u', 'U'},
        {'i', 'I'},
        {'o', 'O'},
        {'p', 'P'},
        {'[', '{'},
        {']', '}'},
        {13, 13},
        {0, 0},
        {'a', 'A'},
        {'s', 'S'},
        {'d', 'D'},
        {'f', 'F'},
        {'g', 'G'},
        {'h', 'H'},
        {'j', 'J'},
        {'k', 'K'},
        {'l', 'L'},
        {';', ':'},
        {39, 34},
        {'`', '~'},
        {0, 0},
        {'\\', '|'},
        {'z', 'Z'},
        {'x', 'X'},
        {'c', 'C'},
        {'v', 'V'},
        {'b', 'B'},
        {'n', 'N'},
        {'m', 'M'},
        {',', '<'},
        {'.', '>'},
        {'/', '?'},
        {0, 0},
        {0, 0},
        {0, 0},
        {' ', ' '},
};

#endif