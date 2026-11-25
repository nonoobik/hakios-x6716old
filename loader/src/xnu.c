#include "board_x6716.h"
#include "xnu_boot.h"

static boot_args_t xnu_args __attribute__((aligned(4096)));

static void simple_strcpy(char *dst, const char *src) {
    while ((*dst++ = *src++));
}

static void simple_memset(void *ptr, int val, uint64_t len) {
    uint8_t *p = (uint8_t *)ptr;
    while (len--) *p++ = (uint8_t)val;
}

void boot_xnu(uint64_t kernel_entry, uint64_t dtb_addr, uint32_t dtb_size) {
    simple_memset(&xnu_args, 0, sizeof(boot_args_t));

    xnu_args.Revision = kBootArgsRevision;
    xnu_args.Version  = kBootArgsVersion;

    /* Карта памяти MT6768 из твоего iomem */
    xnu_args.physBase      = DRAM_BASE;
    xnu_args.virtBase      = 0xFFFFFF8000000000ULL;
    xnu_args.memSize       = 0x100000000ULL; /* 4 ГБ */
    xnu_args.memSizeActual = 0x100000000ULL;

    /* Настройки дисплея X6716 */
    xnu_args.Video.v_baseAddr = FB_BASE_ADDR;
    xnu_args.Video.v_display  = 1;
    xnu_args.Video.v_rowBytes = FB_STRIDE * FB_BPP;
    xnu_args.Video.v_width    = FB_WIDTH;
    xnu_args.Video.v_height   = FB_HEIGHT;
    xnu_args.Video.v_depth    = 32;

    /* Device Tree и аргументы запуска (-v = verbose text log на экран) */
    xnu_args.deviceTreeP      = (void *)dtb_addr;
    xnu_args.deviceTreeLength = dtb_size;
    xnu_args.topOfKernelData  = kernel_entry + 0x02000000ULL;

    simple_strcpy(xnu_args.CommandLine, "-v serial=3 debug=0x14e keepsyms=1 rd=md0");

    /* Сбрасываем кэш перед прыжком в ядро */
    __asm__ volatile("dsb sy\n isb" ::: "memory");

    /* Передаём указатель на boot_args в x0 и прыгаем на точку входа XNU */
    void (*xnu_start)(boot_args_t *) = (void (*)(boot_args_t *))kernel_entry;
    xnu_start(&xnu_args);
}
