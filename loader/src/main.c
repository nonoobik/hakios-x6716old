#include "board_x6716.h"

static inline void writel(uint32_t val, uint64_t addr) {
    *(volatile uint32_t *)addr = val;
}

static inline uint32_t readl(uint64_t addr) {
    return *(volatile uint32_t *)addr;
}

static void wdt_disable(void) {
    /* Сбрасываем и отключаем аппаратный таймер перезагрузки */
    writel(MTK_WDT_RESTART_KEY, MTK_WDT_RESTART);
    writel(MTK_WDT_MODE_KEY, MTK_WDT_MODE);
}

static void uart_putc(char c) {
    while (!(readl(UART_LSR) & 0x20));
    writel((uint32_t)c, UART_THR);
}

static void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}

static void fb_fill(uint32_t color) {
    volatile uint32_t *fb = (volatile uint32_t *)FB_BASE_ADDR;
    for (uint32_t y = 0; y < FB_HEIGHT; y++) {
        for (uint32_t x = 0; x < FB_WIDTH; x++) {
            fb[y * FB_STRIDE + x] = color;
        }
    }
    /* Очистка кэша данных, чтобы контроллер дисплея увидел изменения в RAM */
    __asm__ volatile("dsb sy" ::: "memory");
}

void loader_main(void) {
    wdt_disable();
    uart_puts("\n[X6716] mtkloader fbdiag started!\n");

    /* Заливаем экран ярко-зелёным (ARGB: 0xFF00FF00) */
    fb_fill(0xFF00FF00);
    uart_puts("[X6716] Framebuffer filled at 0x77520000\n");

    while (1) {
        __asm__ volatile("wfe");
    }
}
