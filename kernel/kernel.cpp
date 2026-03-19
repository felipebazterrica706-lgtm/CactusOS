#include "../drivers/screen.h"

void check_key(); // Le avisamos que existe

extern "C" void kmain() {
    clear_screen(0x1F); // Fondo azul
    kprint("--- CACTUS-OS INTERACTIVO ---", 0, 0, 0x1E);
    kprint("Escribi algo:", 2, 0, 0x0F);

    while(1) {
        check_key(); // Revisa el teclado millones de veces por segundo
    }
}