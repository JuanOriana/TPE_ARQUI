#ifndef KEY_MAP_H
#define KEY_MAP_H

static const char keyMap[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',                   /* 9 */
        '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',              /* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,                 /* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',                /* 39 */
        '\'', '`', 0, /*Left Shift*/ '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
        'm', ',', '.', '/', 0, /*Right Shift*/ '*',                      /*55*/
        0,                                                               /* Alt -56*/
        ' ',                                                             /* Space bar -57*/
        0,                                                               /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                /* < ... F10 */
        0,                                                               /* Num lock -68*/
        0,                                                               /* Scroll Lock -69*/
        0,                                                               /* Home key -70*/
        17,                                                              /* Up Arrow -71*/
        0,                                                               /* Page Up -72*/
        '-',                                                             /* Minus -73*/
        18,                                                              /* Left Arrow */
        0,
        20,  /* Right Arrow */
        '+', /* Plus -78*/
        0,   /* 79 - End key*/
        19,  /* Down Arrow */
        0,   /* Page Down */
        0,   /* Insert Key */
        0,   /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

#endif