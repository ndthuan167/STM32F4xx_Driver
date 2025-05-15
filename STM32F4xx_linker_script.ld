MEMORY
{ 
    FLASH (rx):ORIGIN=0x08000000,LENGTH=1M          /*Flashmemory*/
    RAM(xrw): ORIGIN = 0x20020000, LENGTH = 128K    /* SRAM */
}

SECTIONS
{
    /* The startup code and the vector table */
    .isr_vector :
    {
        KEEP(*(.isr_vector))  /* Interrupt vector table */
    } > FLASH

    /* The .text section contains the code */
    .text :
    {
        *(.text*)             /* All .text sections from all files */
        *(.rodata*)           /* Read-only data */
        *(.rodata*)           /* Read-only data */
    } > FLASH

    /* The .data section contains initialized data */
    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        *(.data*)
    } > RAM

    /* The .bss section contains uninitialized data */
    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM

    /* Stack and heap */
    ._stack (NOLOAD) :
    {
        . = ALIGN(8);
        . = . + 0x800; /* Reserve 2KB for stack */
    } > RAM

    ._heap (NOLOAD) :
    {
        . = ALIGN(8);
        . = . + 0x2000; /* Reserve 8KB for heap */
    } > RAM
}

/* .data in FLASH */
PROVIDE(start_data_in_flash = LOADADDR(.data));
PROVIDE(end_data_in_flash = LOADADDR(.data) + SIZEOF(.data));

/* .data in RAM */
PROVIDE(start_data_in_RAM = ADDR(.data));
PROVIDE(end_data_in_RAM = ADDR(.data) + SIZEOF(.data));

/* .bss in RAM */
PROVIDE(start_bss_in_RAM = ADDR(.bss));
PROVIDE(end_bss_in_RAM = ADDR(.bss) + SIZEOF(.bss));