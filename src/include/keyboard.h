#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "include/IO.h" 
#include "include/UI.h"

int shift_pressed;

static const char scancode_de_normal[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, '\'', '\b', '\t', // 0x00 - 0x0F
    'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 0, '+', '\n',  0,  'a', 's', // 0x10 - 0x1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, '#', 0,   '<', 'y', 'x', 'c',       // 0x20 - 0x2F
    'v', 'b', 'n', 'm', ',', '.', '-', 0,   '*', 0,   ' ', 0,   0,    0,   0,   0,   // 0x30 - 0x3F
};

static const char scancode_de_shift[128] = {
    0,  27, '!', '"', 0, '$', '%', '&', '/', '(', ')', '=', '?', '`', '\b', '\t', // 0x00 - 0x0F
    'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 0, '*', '\n', 0,  'A', 'S', // 0x10 - 0x1F
    'D', 'F', 'G', 'H', 'J', 'K', 'L', 0, 0, '\'', 0,  '>', 'Y', 'X', 'C',      // 0x20 - 0x2F
    'V', 'B', 'N', 'M', ';', ':', '_', 0,   '*', 0,   ' ', 0,   0,    0,   0,   0,  // 0x30 - 0x3F
};

static inline int kbd_data_ready(void) {
    return inb(0x64) & 1; // Bit 0 = Output buffer full
}

static uint8_t read_scancode(void) {
    while (!kbd_data_ready()) {
        __asm__ volatile ("pause");
    }
    return inb(0x60);
}

char keypress_blocking(void) {
    uint8_t code = read_scancode();
    char ch;

    if (code & 0x80) {
        code = code & 0x7F;
        if (code == 42 || code  == 54){
            shift_pressed = 0;
        }
        return '\0';
    }
    else{
        if (code  == 42 || code  == 54){
            shift_pressed = 1;
        }
    }

    if(shift_pressed){
        ch = scancode_de_shift[code & 0x7F];
    }
    else{
        ch = scancode_de_normal[code & 0x7F];
    }

    return ch ? ch : '\0';
}

char keypress_unblocking(void) {
    if(!kbd_data_ready()){
        return '\0';
    }
    uint8_t code = inb(0x60);
    char ch;

    if (code & 0x80) {
        code = code & 0x7F;
        if (code == 42 || code  == 54){
            shift_pressed = 0;
        }
        return '\0';
    }
    else{
        if (code  == 42 || code  == 54){
            shift_pressed = 1;
        }
    }

    if(shift_pressed){
        ch = scancode_de_shift[code & 0x7F];
    }
    else{
        ch = scancode_de_normal[code & 0x7F];
    }

    return ch ? ch : '\0';
}




#endif