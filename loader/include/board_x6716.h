#ifndef BOARD_X6716_H
#define BOARD_X6716_H

#include <stdint.h>

/* Карта ОЗУ из iomem */
#define DRAM_BASE           0x40000000ULL
#define KERNEL_LOAD_ADDR    0x40080000ULL

/* Фреймбуфер из dmesg (disphal_allocate_fb) */
#define FB_BASE_ADDR        0x77520000ULL
#define FB_SIZE             0x022E0000ULL
#define FB_WIDTH            1080
#define FB_HEIGHT           2400
#define FB_STRIDE           1088
#define FB_BPP              4

/* Watchdog (toprgu@10007000) */
#define MTK_WDT_BASE        0x10007000ULL
#define MTK_WDT_MODE        (MTK_WDT_BASE + 0x00)
#define MTK_WDT_RESTART     (MTK_WDT_BASE + 0x08)
#define MTK_WDT_MODE_KEY    0x22000000U
#define MTK_WDT_RESTART_KEY 0x1971U

/* UART0 (11002000.serial) */
#define UART0_BASE          0x11002000ULL
#define UART_THR            (UART0_BASE + 0x00)
#define UART_LSR            (UART0_BASE + 0x14)

#endif
