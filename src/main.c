#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "include/limine.h"
#include "include/memop.h"
#include "include/hexcolor.h"
#include "include/UI.h"
#include "include/general.h"

int main_setup(void){
    // Ensure the bootloader actually understands our base revision (see spec).
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
    draw_string("WELCOME TO SIGMA OS", 80, height/2 , WHITE, 6);
    hcf();
}