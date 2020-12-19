OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH( "riscv" )
ENTRY( reset_handler )

MEMORY
{ 
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 32K 
/* Consider
  FLASH (rxai!w) : ORIGIN = 0x00000000, LENGTH = 128K
  RAM (wxa!ri) : ORIGIN = 0x20000000, LENGTH = 32K
as more descriptive.
*/
}


SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 1K;
  .vector_table :
  {
    _END_OF_FLASH = . + 128K;
    KEEP (*(SORT_NONE(.vector_table)))
  } >FLASH

  .text :
  {
    *(.text .text.*)
    *(.rodata .rodata.*)  
    *(.srodata .srodata.*)
  } >FLASH

  . = ALIGN(4);

/*  PROVIDE (__etext = .); */
  PROVIDE (_etext = .);
/*  PROVIDE (etext = .); */
  PROVIDE( __global_pointer$ = . + (4K / 2) );

  _sidata = .;

  .data : AT( _sidata )
  {
    _END_OF_RAM = . + 32K;
    _sdata = .;
    *(.rdata) 
    *(.data .data.*)
    *(.sdata .sdata.*)
    . = ALIGN(4);
    _edata = .;
  } >RAM

  PROVIDE( _edata = . );
  PROVIDE( edata = . );
  PROVIDE( _fbss = . );
  PROVIDE( __bss_start = . );

  .bss :
  {
    _sbss = .;
    *(.sbss*)
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  . = ALIGN(8);
  PROVIDE( _kend = .);
  PROVIDE( _end = . );
  PROVIDE( end = . );

  .stack ORIGIN(RAM) + LENGTH(RAM) - __stack_size :
  {
    PROVIDE( _heap_end = . ); 
    . = __stack_size;  
    PROVIDE( _sp = . ); 
  } >RAM
}
