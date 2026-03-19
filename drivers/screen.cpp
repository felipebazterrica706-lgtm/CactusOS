#include "screen.h"
void clear_screen(char color) {
    char* vid = (char*)0xB8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) { vid[i] = ' '; vid[i+1] = color; }
}
void kprint(const char* m, int r, int c, char col) {
    char* vid = (char*)0xB8000;
    int off = (r * 80 + c) * 2;
    for (int i = 0; m[i] != '\0'; i++) { vid[off+(i*2)] = m[i]; vid[off+(i*2)+1] = col; }
}
