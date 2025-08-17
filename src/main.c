#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "include/limine.h"
#include "include/memop.h"
#include "include/hexcolor.h"
#include "include/UI.h"
#include "include/general.h"
#include "include/sound.h"
#include "include/string_ops.h"
#include "include/var.h"
#include "include/clock.h"
#include "include/keyboard.h"
#include "include/shell.h"


int main_setup(void){
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    UI_setup();

    return 0;
}

void kmain(void) {

    if(main_setup() != 0){
        hcf();
    }

    fill_screen(BLACK);
    {
        char buffer[64];
        draw_string(merge_char("Welcome to ", osname, buffer), 80, height/2 , WHITE, 6);
    }

    wait_ms(2000);
    while(1){
        shell_main();
    }   


    //play_sound(1000);
    hcf();
}