#ifndef UI_H
#define UI_H

#include "include/hexcolor.h"
#include "include/font8x8.h"
#include "include/general.h"

#define space 1

size_t width;
size_t height;
size_t pitch;
struct limine_framebuffer *framebuffer;
uint32_t *fb_ptr;


void UI_setup(void){
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
    width = framebuffer->width;
    height = framebuffer->height;
    pitch = framebuffer->pitch / 4;
    fb_ptr = (uint32_t *)framebuffer->address;
}

void draw_char(int x, int y, char c, uint32_t color, int scale) {


    if (c < 32 || c > 127) return;

    const uint8_t* glyph = font8x8_extended[c - 32];

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (glyph[row] & (1 << col)) {
                int px = x + col * scale;
                int py = y + row * scale;

                for (int dy = 0; dy < scale; dy++) {
                    for (int dx = 0; dx < scale; dx++) {
                        int fx = px + dx;
                        int fy = py + dy;

                        if (fx >= 0 && fx < (int)width && fy >= 0 && fy < (int)height)
                            fb_ptr[fy * pitch + fx] = color;
                    }
                }
            }
        }
    }
}

void fill_screen(uint32_t color) {

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            fb_ptr[y * pitch + x] = color;
        }
    }
}

void draw_string(const char* msg, int x, int y, uint32_t color, int scale){
    int xx = x;
    for(int i = 0; msg[i] != '\0'; i++){
        draw_char(xx, y, msg[i], color, scale);
        xx += 8*scale + space*scale;
    }
}

void terminal(void){
    fill_screen(BLACK);
    
}


#endif