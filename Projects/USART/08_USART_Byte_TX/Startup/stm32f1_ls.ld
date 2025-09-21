/* Define the entry point of the program */
ENTRY(Reset_Handler)

/* Define the memory regions of the STM32F103C8T6 */
MEMORY
{
  /* Flash memory: for storing code and read-only data */
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
  /* SRAM memory: for stack, heap, global/static variables */
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Set the initial stack pointer to the end of RAM */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Define minimum sizes for heap (1kB) and stack (1kB)*/
_Min_Heap_Size = 0x400;
_Min_Stack_Size = 0x400;

/* Define all output sections */
SECTIONS
{
  /* Code and read-only data section (stored in FLASH) */
  .text :
  {
    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Keep the interrupt vector table (important for startup) */
    KEEP(*(.isr_vector))

    /* Include all executable code sections */
    *(.text*)

    /* Include all constant read-only data */
    *(.rodata*)

    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Mark the end of the .text section */
    _etext = .;
  } > FLASH

  /* Initialized data section (stored in RAM, loaded from FLASH) */
  .data : 
  {
    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Mark the start of .data in RAM */
    _sdata = .;

    /* Include all initialized global/static variables */
    *(.data*)

    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Mark the end of .data in RAM */
    _edata = .;
  } > RAM AT > FLASH

  /* Store FLASH load address of .data section */
  _sidata = LOADADDR(.data);

  /* Uninitialized data section (BSS), stored in RAM */
  .bss :
  {
    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Mark the start of BSS section */
    _sbss = .;

    /* Include all uninitialized global/static variables */
    *(.bss*)

    /* Include any common variables not explicitly in .bss */
    *(COMMON)

    /* Mark the end of BSS section */
    _ebss = .;
  } > RAM

  /* Heap section: required for dynamic allocation */
  .heap (COPY):
  {
    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Mark start of heap */
    _sheap = .;

    /* Reserve minimum heap space */
    . = . + _Min_Heap_Size;

    /* Align word to 4-byte boundary */
    . = ALIGN(4);

    /* Mark end of heap */
    _eheap = .;
  } > RAM

  /* Stack section: grows downward from end of RAM */
  .stack (COPY):
  {
    /* Align stack to 8 bytes */
    . = ALIGN(8);

    /* Mark start of stack */
    _sstack = .;

    /* Reserve minimum stack space */
    . = . + _Min_Stack_Size;

    /* Align stack to 8 bytes */
    . = ALIGN(8);

    /* Mark end of stack (top of RAM) */
    _estack = ORIGIN(RAM) + LENGTH(RAM);
  } > RAM

  /* Optional symbol marking end of memory layout */
  _end = .;
  /* For dynamic memory allocation */
  PROVIDE(end = _eheap);
}
