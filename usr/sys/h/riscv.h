
// Supervisor Status Register, sstatus
#define SSTATUS_SPP (1L << 8)  // Previous mode, 1=Supervisor, 0=User
#define SSTATUS_SPIE (1L << 5) // Supervisor Previous Interrupt Enable
#define SSTATUS_UPIE (1L << 4) // User Previous Interrupt Enable
#define SSTATUS_SIE (1L << 1)  // Supervisor Interrupt Enable
#define SSTATUS_UIE (1L << 0)  // User Interrupt Enable
// Supervisor Interrupt Enable
#define SIE_SEIE (1L << 9) // external
#define SIE_STIE (1L << 5) // timer
#define SIE_SSIE (1L << 1) // software

static inline unsigned long
get_sie()
{
  unsigned long x;
  asm volatile("csrr %0, sie" : "=r" (x) );
  return x;
}

static inline void
set_sie(unsigned long x)
{
  asm volatile("csrw sie, %0" : : "r" (x));
}

// Machine-mode Interrupt Enable
#define MIE_MEIE (1L << 11) // external
#define MIE_MTIE (1L << 7)  // timer
#define MIE_MSIE (1L << 3)  // software
static inline unsigned long
get_mie()
{
  unsigned long x;
  asm volatile("csrr %0, mie" : "=r" (x) );
  return x;
}

static inline void
set_mie(unsigned long x)
{
  asm volatile("csrw mie, %0" : : "r" (x));
}


// Machine-mode interrupt vector
static inline void
set_mtvec(unsigned long x)
{
  asm volatile("csrw mtvec, %0" : : "r" (x));
}

static inline unsigned long
get_sstatus()
{
  unsigned long x;
  asm volatile("csrr %0, sstatus" : "=r" (x) );
  return x;
}

static inline void
set_sstatus(unsigned long x)
{
  asm volatile("csrw sstatus, %0" : : "r" (x));
}

// Machine Status Register, mstatus

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)    // machine-mode interrupt enable.

static inline unsigned long
get_mstatus()
{
  unsigned long x;
  asm volatile("csrr %0, mstatus" : "=r" (x) );
  return x;
}

static inline void
set_mstatus(unsigned long x)
{
  asm volatile("csrw mstatus, %0" : : "r" (x));
}

static inline unsigned long
get_mhartid()
{
  unsigned long x;
  asm volatile("csrr %0, mhartid" : "=r" (x) );
  return x;
}

#if 0
// Supervisor Interrupt Enable
#define SIE_SEIE (1L << 9) // external
#define SIE_STIE (1L << 5) // timer
#define SIE_SSIE (1L << 1) // software
static inline unsigned long
get_sie()
{
  unsigned long x;
  asm volatile("csrr %0, sie" : "=r" (x) );
  return x;
}

static inline void
set_sie(unsigned long x)
{
  asm volatile("csrw sie, %0" : : "r" (x));
}
#endif


static inline void
intr_enable() {
//  set_sie(get_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);
//  set_sie(get_sie() | SIE_SSIE );
//  set_sstatus(get_sstatus() | SSTATUS_SIE);

  // enable machine-mode interrupts.
  set_mstatus(get_mstatus() | MSTATUS_MIE);

 // enable machine-mode timer interrupts.
  set_mie(get_mie() | MIE_MTIE);
}

static inline void
intr_disable()
{
  w_sstatus(r_sstatus() & ~SSTATUS_SIE);
}

static inline int
intr_enabled()
{
  unsigned long x = r_sstatus();
  return (x & SSTATUS_SIE) != 0;
}

// Machine Exception Delegation
static inline unsigned long
get_medeleg()
{
  unsigned long x;
  asm volatile("csrr %0, medeleg" : "=r" (x) );
  return x;
}

static inline void
set_medeleg(unsigned long x)
{
  asm volatile("csrw medeleg, %0" : : "r" (x));
}

// Machine Interrupt Delegation
static inline unsigned long
get_mideleg()
{
  unsigned long x;
  asm volatile("csrr %0, mideleg" : "=r" (x) );
  return x;
}

static inline void
set_mideleg(unsigned long x)
{
  asm volatile("csrw mideleg, %0" : : "r" (x));
}

static inline unsigned long
get_mepc()
{
  unsigned long x;
  asm volatile("csrr %0, mepc" : "=r" (x) );
  return x;
}

static inline unsigned long
get_sepc()
{
  unsigned long x;
  asm volatile("csrr %0, sepc" : "=r" (x) );
  return x;
}
static inline unsigned long
get_mcause()
{
  unsigned long x;
  asm volatile("csrr %0, mcause" : "=r" (x) );
  return x;
}

static inline unsigned long
get_scause()
{
  unsigned long x;
  asm volatile("csrr %0, scause" : "=r" (x) );
  return x;
}

#if 0
static inline unsigned long
get_sstatus()
{
  unsigned long x;
  asm volatile("csrr %0, sstatus" : "=r" (x) );
  return x;
}
#endif


static inline void
set_mscratch(unsigned long x)
{
  asm volatile("csrw mscratch, %0" : : "r" (x));
}

