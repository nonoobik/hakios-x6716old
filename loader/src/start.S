.section ".text.boot"
.global _start

_start:
    /* Стандартный 64-байтный заголовок Linux ARM64 Image для LK */
    b       real_start              /* code0: прыжок на код */
    .word   0                       /* code1 */
    .quad   0x00080000              /* text_offset: 512 KB (0x40080000) */
    .quad   0x00100000              /* image_size: 1 MB */
    .quad   0x00000002              /* flags: little-endian, 4K pages */
    .quad   0                       /* res2 */
    .quad   0                       /* res3 */
    .quad   0                       /* res4 */
    .ascii  "ARM\x64"               /* magic: обязательная сигнатура */
    .word   0                       /* res5 */

real_start:
    /* Отключаем прерывания */
    msr     daifset, #0xf

    /* Настраиваем стек в безопасной зоне ОЗУ (0x50000000) */
    ldr     x0, =0x50000000
    mov     sp, x0

    /* Переходим в C-код */
    bl      loader_main

hang:
    wfe
    b       hang
