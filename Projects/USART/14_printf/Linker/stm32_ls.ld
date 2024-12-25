/* 
	NOTES: 
		- '*' is wildcard character used to convey merge of all .text section of all the input files 
		- '.' is a location counter used to retrieve current VMA location
		- Virtual Memory Address (VMA): The address at which a piece of code or data will be executed or accessed in memory. It represents the logical address space as perceived by the program.
		- Load Memory Address (LDA): The physical address where a piece of code or data is stored in memory when the program is loaded. It reflects the actual address in the device's memory where the binary is stored.
		- Basic Syntax Understanding 
		SECTIONS{
			VMA != LMA
			.section_name{
			
			} > VMA AT> LMA
			VMA == LMA
			.section_name{
			
			} > LMA
		}
*/

/* Entry Point */
ENTRY(Reset_Handler);

/* Memory Arrangement & Address: STM32F103xx_Flash_Reference_Manual.pdf */
MEMORY {
	FLASH(rx): ORIGIN = 0x08000000, LENGTH = 64K
	SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

/* Symbol Declaration: Mapping between Variable Name and Address */
__estack = ORIGIN(SRAM) + LENGTH(SRAM);
__max_heap_size = 0x200;
__max_stack_size = 0x400;

/* Partition of Data */
SECTIONS {

	/* Vector Table */
	.isr_vector : {
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Start of .isr_vector */
		_svector = .;
		/* Vector Table */
		KEEP(*(.isr_vector))
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* End of .isr_vector */
		_evector = .;
	}> FLASH

	/* Code or Instructions */
	.text : {
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Start of .text */
		_stext = .;
		/* Text Section of all the input files (Code Section) */
		*(.text*)
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* End of .text */
		_etext = .;
	} > FLASH

	/* 'const' data */
	.rodata : {
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Start of .rodata Section */
		_srodata = .;
		/* Read Only Data (const) */
		*(.rodata*)
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Storing the end of .rodata section */
		_erodata = .;
	}> FLASH

	/* SRAM (VMA) & FLASH (LMA) */
	.data : {
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Storing the start of .data VMA section */
		_sdata = .;
		/* Data Section of all the input files */
		*(.data*)
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Storing the end of .data VMA section */
		_edata = .;
	} > SRAM AT > FLASH

	/* Storing the start address of .data LMA section */
	_sidata = LOADADDR(.data);

	/* Uninitialized Data */
	.bss : {
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Storing the start of .bss VMA section */
		_sbss = .;
		__bss_start__ = .;
		/* Uninitialized Section of all the input files */
		*(.bss*)
		/* Align with word (4 bytes) */
		. = ALIGN(4);
		/* Storing the end of .bss VMA section */
		_ebss = .;
		__bss_end__ = .;
	} > SRAM 
}
