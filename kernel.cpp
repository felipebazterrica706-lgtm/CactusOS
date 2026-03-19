extern "C" void kmain() {
    char* vid = (char*)0xB8000;
    
    // Limpiar pantalla (Azul)
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vid[i] = ' ';
        vid[i+1] = 0x1F;
    }

    // Escribir mensaje
    const char* msg = "CACTUS-OS: MODO EMERGENCIA ACTIVO";
    for (int i = 0; msg[i] != '\0'; i++) {
        vid[i*2] = msg[i];
        vid[i*2+1] = 0x1E;
    }

    // Bucle de teclado ultra simple
    while(1) {
        unsigned char scancode;
        __asm__("in %%dx, %%al" : "=a" (scancode) : "d" (0x60));
        
        if (scancode == 0x1E) { // Si tocas la 'A'
            vid[160] = 'A';
            vid[161] = 0x1F;
        }
    }
}
