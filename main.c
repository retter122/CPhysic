#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./CPhysic/cphysic.h"


static window_gl *PWindow = 0;


int main() {
    init_gl();

    PWindow = window_gl_create(800, 800, "test");
    window_gl_clear_color(PWindow, 0.3, 0.6, 0.3, 0.4);

    while (1) {
        if (window_gl_should_close(PWindow)) break;
        window_gl_clear(PWindow);


    }

    return 0;
}
