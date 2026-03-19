# Limpiamos la carpeta bin para que no haya archivos viejos
if (!(Test-Path "bin")) { mkdir bin }
Remove-Item bin\* -ErrorAction SilentlyContinue

Write-Host "--- COMPILANDO CACTUS-OS ---" -ForegroundColor Cyan

# Paso 1: El Boot (Si el archivo de arriba esta bien, esto NO falla)
nasm -f bin boot/boot.asm -o bin/boot.bin

# Paso 2: El Kernel y los Drivers
g++ -m32 -ffreestanding -fno-stack-protector -fno-pie -nostdlib -c kernel/kernel.cpp -o bin/kernel.o
g++ -m32 -ffreestanding -fno-stack-protector -fno-pie -nostdlib -c drivers/screen.cpp -o bin/screen.o
g++ -m32 -ffreestanding -fno-stack-protector -fno-pie -nostdlib -c drivers/keyboard.cpp -o bin/keyboard.o

# Paso 3: Linker (Unir todo en el .exe y despues al .bin)
ld -m i386pe -Ttext 0x1000 bin/kernel.o bin/screen.o bin/keyboard.o -o bin/kernel.exe
objcopy -O binary bin/kernel.exe bin/kernel.bin

# Paso 4: Crear el CactusOS.bin final (Pegando Boot + Kernel)
$boot = [System.IO.File]::ReadAllBytes("$pwd/bin/boot.bin")
$kern = [System.IO.File]::ReadAllBytes("$pwd/bin/kernel.bin")
$final = $boot + $kern
[System.IO.File]::WriteAllBytes("$pwd/CactusOS.bin", $final)

Write-Host "--- ¡EXITO! ARRANCANDO QEMU ---" -ForegroundColor Green
& "C:\Program Files\qemu\qemu-system-i386.exe" -drive format=raw,file=CactusOS.bin