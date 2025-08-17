#ifndef SHELL_H
#define SHELL_H

#include "include/UI.h"
#include "include/string_ops.h"
#include "include/keyboard.h"

#define shell_fontsize 3

const char *shell_path = "/test/user/: ";

int print_x = 30;
int print_y = 30;
int shell_buffer_mod = 0;

char shell_buffer[512];

void print_string(const char *msg)
{
    // draw_string(msg, print_x, print_y, color, shell_fontsize);
    for (int i = 0; i < len(msg); i++)
    {
        switch (msg[i])
        {
        case '\n':
        {
            print_y += (8 * shell_fontsize) / 2;
            shell_buffer[0] = '\0';
            print_string(shell_path);
            break;
        }
        case '\b':
        {
            if (len(shell_buffer) > len(shell_path))
            {
                shell_buffer[len(shell_buffer) - 1] = '\0';
            }
            break;
        }
        default:
        {
            shell_buffer[len(shell_buffer)] = msg[i];
            break;
        }
        }
    }
}

void print_char(const char ch)
{
        switch (ch)
        {
        case '\n':
        {
            print_y += (8 * shell_fontsize) / 2;
            shell_buffer[0] = '\0';
            print_string(shell_path);
            break;
        }
        case '\b':
        {
            if (len(shell_buffer) > len(shell_path))
            {
                shell_buffer[len(shell_buffer) - 1] = '\0';
            }
            break;
        }
        default:
        {
            shell_buffer[len(shell_buffer)] += ch;
            break;
        }
        }
}

void shell_init(void)
{
    fill_screen(BLACK);
}

void shell_main(void)
{
    fill_screen(BLACK);
    draw_string(shell_buffer, print_x, print_y, WHITE, shell_fontsize);
    print_char(keypress_unblocking());
}

#endif