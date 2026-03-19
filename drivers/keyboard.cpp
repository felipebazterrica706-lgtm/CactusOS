#include "screen.h"

// Función para leer del puerto del teclado
unsigned char inb(unsigned short port) {
    unsigned char res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

// Mapa de caracteres simple (puedes agregar más después)
char kbd_map[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

int cursor_x = 0; // Para saber dónde escribir la próxima letra

void check_key() {
    unsigned char status = inb(0x64); // Chequear si el teclado tiene datos
    if (status & 0x01) {
        unsigned char scancode = inb(0x60);
        
        // Si el scancode es menor a 128 (tecla presionada, no soltada)
        if (scancode < 128 && kbd_map[scancode] != 0) {
            char letra[2] = { kbd_map[scancode], '\0' };
            kprint(letra, 5, cursor_x, 0x0F); // Escribe en la fila 5
            cursor_x++; // Mueve el cursor a la derecha
        }
    }
}