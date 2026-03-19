[bits 16]
[org 0x7c00]
start:
    mov ax, 0x03
    int 0x10
    mov ah, 0x02
    mov al, 15
    mov ch, 0
    mov dh, 0
    mov cl, 2
    mov bx, 0x1000
    int 0x13
    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:init32
[bits 32]
init32:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov ebp, 0x90000
    mov esp, ebp
    call 0x1000
    jmp $
gdt_start:
    dq 0
gdt_code:
    dw 0xffff, 0, 0x9a00, 0x00cf
gdt_data:
    dw 0xffff, 0, 0x9200, 0x00cf
gdt_end:
gdt_desc:
    dw gdt_end-gdt_start-1
    dd gdt_start
times 510-($-$$) db 0
dw 0xAA55