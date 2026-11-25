#ifndef XNU_BOOT_H
#define XNU_BOOT_H

#include <stdint.h>

#define BOOT_LINE_LENGTH        608
#define kBootArgsRevision       2
#define kBootArgsVersion        2

typedef struct boot_video {
    uint64_t v_baseAddr;    /* Физический адрес экрана (0x77520000) */
    uint64_t v_display;     /* 1 = графический режим */
    uint64_t v_rowBytes;    /* Байтов в строке (stride * 4) */
    uint64_t v_width;       /* 1080 */
    uint64_t v_height;      /* 2400 */
    uint64_t v_depth;       /* 32 бита */
} boot_video_t;

typedef struct boot_args {
    uint16_t     Revision;
    uint16_t     Version;
    uint64_t     virtBase;          /* Виртуальная база ядра */
    uint64_t     physBase;          /* Физическая база ОЗУ (0x40000000) */
    uint64_t     memSize;           /* Размер ОЗУ */
    uint64_t     topOfKernelData;   /* Конец данных ядра в памяти */
    boot_video_t Video;
    uint32_t     machineType;
    void         *deviceTreeP;      /* Указатель на Device Tree */
    uint32_t     deviceTreeLength;
    char         CommandLine[BOOT_LINE_LENGTH];
    uint64_t     bootFlags;
    uint64_t     memSizeActual;
} boot_args_t;

void boot_xnu(uint64_t kernel_entry, uint64_t dtb_addr, uint32_t dtb_size);

#endif
