#if 0
// 2020-10-03: These are absolutely for QEMU and not the GD32V. 
// Super frustrating

// Mappings for QEMU. Maybe not for real hardware...
#define UART0 0x10000000L
#define UART0_IRQ 10

// virtio mmio interface
#define VIRTIO0 0x10001000L
#define VIRTIO0_IRQ 1

// Local interrupt controller
#define CLINT 0x02000000L
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 8*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

// #define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 8*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

#define PLIC 0xc000000L

#else
// #define TIMER_CTRL_ADDR 0xd1000000
// #define TIMER_MTIME (TIMER_CTRL_ADDR + 0)
// #define TIMER_MTIMECMP (TIMER_CTRL_ADDR + 8)
#endif
