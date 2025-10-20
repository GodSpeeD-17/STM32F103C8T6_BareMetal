	.cpu cortex-m3
	.arch armv7-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"systick.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "/home/shrey_shah/STM32F103C8T6/Projects/DMA/11_DMA_Transfer/Src/systick.c"
	.section	.bss.tickCount,"aw",%nobits
	.align	2
	.type	tickCount, %object
	.size	tickCount, 4
tickCount:
	.space	4
	.section	.text.SysTick_Get_Ticks,"ax",%progbits
	.align	1
	.global	SysTick_Get_Ticks
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Get_Ticks, %function
SysTick_Get_Ticks:
.LFB119:
	.loc 1 16 33
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI0:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	add	r7, sp, #0
.LCFI1:
	.cfi_def_cfa_register 7
	.loc 1 18 9
	ldr	r3, .L3
	ldr	r3, [r3]
	.loc 1 19 1
	mov	r0, r3
	mov	sp, r7
.LCFI2:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI3:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
.L4:
	.align	2
.L3:
	.word	tickCount
	.cfi_endproc
.LFE119:
	.size	SysTick_Get_Ticks, .-SysTick_Get_Ticks
	.section	.text.SysTick_Set_Ticks,"ax",%progbits
	.align	1
	.global	SysTick_Set_Ticks
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Set_Ticks, %function
SysTick_Set_Ticks:
.LFB120:
	.loc 1 26 44
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI4:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #12
.LCFI5:
	.cfi_def_cfa_offset 16
	add	r7, sp, #0
.LCFI6:
	.cfi_def_cfa_register 7
	str	r0, [r7, #4]
.LBB22:
.LBB23:
.LBB24:
.LBB25:
	.file 2 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
	.loc 2 156 3
	.syntax unified
@ 156 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 1
	cpsid i
@ 0 "" 2
	.loc 2 157 1
	.thumb
	.syntax unified
	nop
.LBE25:
.LBE24:
	.file 3 "/home/shrey_shah/STM32F103C8T6/Projects/DMA/11_DMA_Transfer/Inc/systick.h"
	.loc 3 56 36
	ldr	r3, .L6
	.loc 3 56 42
	ldr	r3, [r3]
	.loc 3 56 36
	ldr	r2, .L6
	.loc 3 56 47
	bic	r3, r3, #1
	str	r3, [r2]
.LBB26:
.LBB27:
	.loc 2 145 3
	.syntax unified
@ 145 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 1
	cpsie i
@ 0 "" 2
	.loc 2 146 1
	.thumb
	.syntax unified
	nop
.LBE27:
.LBE26:
	.loc 3 59 1
	nop
.LBE23:
.LBE22:
	.loc 1 30 12
	ldr	r2, .L6+4
	ldr	r3, [r7, #4]
	str	r3, [r2]
	.loc 1 32 57
	ldr	r3, [r7, #4]
	subs	r3, r3, #1
	.loc 1 32 36
	ldr	r2, .L6
	.loc 1 32 62
	bic	r1, r3, #-16777216
	.loc 1 32 42
	ldr	r3, [r2, #8]
	bfi	r3, r1, #0, #24
	str	r3, [r2, #8]
.LBB28:
.LBB29:
.LBB30:
.LBB31:
	.loc 2 156 3
	.syntax unified
@ 156 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 1
	cpsid i
@ 0 "" 2
	.loc 2 157 1
	.thumb
	.syntax unified
	nop
.LBE31:
.LBE30:
	.loc 3 44 36
	ldr	r3, .L6
	.loc 3 44 42
	ldr	r3, [r3]
	.loc 3 44 36
	ldr	r2, .L6
	.loc 3 44 47
	orr	r3, r3, #1
	str	r3, [r2]
.LBB32:
.LBB33:
	.loc 2 145 3
	.syntax unified
@ 145 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 1
	cpsie i
@ 0 "" 2
	.loc 2 146 1
	.thumb
	.syntax unified
	nop
.LBE33:
.LBE32:
	.loc 3 47 1
	nop
.LBE29:
.LBE28:
	.loc 1 35 1
	nop
	adds	r7, r7, #12
.LCFI7:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI8:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI9:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
.L7:
	.align	2
.L6:
	.word	-536813552
	.word	tickCount
	.cfi_endproc
.LFE120:
	.size	SysTick_Set_Ticks, .-SysTick_Set_Ticks
	.section	.text.SysTick_Config,"ax",%progbits
	.align	1
	.global	SysTick_Config
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Config, %function
SysTick_Config:
.LFB121:
	.loc 1 43 42
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #12
.LCFI11:
	.cfi_def_cfa_offset 16
	add	r7, sp, #0
.LCFI12:
	.cfi_def_cfa_register 7
	str	r0, [r7, #4]
	.loc 1 45 36
	ldr	r3, .L9
	.loc 1 45 47
	movs	r2, #0
	str	r2, [r3]
	.loc 1 47 59
	ldr	r3, [r7, #4]
	subs	r3, r3, #1
	.loc 1 47 36
	ldr	r2, .L9
	.loc 1 47 64
	bic	r1, r3, #-16777216
	.loc 1 47 43
	ldr	r3, [r2, #4]
	bfi	r3, r1, #0, #24
	str	r3, [r2, #4]
	.loc 1 49 58
	ldr	r3, [r7, #4]
	subs	r3, r3, #1
	.loc 1 49 36
	ldr	r2, .L9
	.loc 1 49 63
	bic	r1, r3, #-16777216
	.loc 1 49 42
	ldr	r3, [r2, #8]
	bfi	r3, r1, #0, #24
	str	r3, [r2, #8]
	.loc 1 51 36
	ldr	r3, .L9
	.loc 1 51 47
	movs	r2, #6
	str	r2, [r3]
	.loc 1 52 1
	nop
	adds	r7, r7, #12
.LCFI13:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI14:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI15:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
.L10:
	.align	2
.L9:
	.word	-536813552
	.cfi_endproc
.LFE121:
	.size	SysTick_Config, .-SysTick_Config
	.section	.text.SysTick_Handler,"ax",%progbits
	.align	1
	.global	SysTick_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Handler, %function
SysTick_Handler:
.LFB122:
	.loc 1 83 27
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI16:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	add	r7, sp, #0
.LCFI17:
	.cfi_def_cfa_register 7
	.loc 1 87 11
	ldr	r3, .L12
	ldr	r3, [r3]
	adds	r3, r3, #1
	ldr	r2, .L12
	str	r3, [r2]
	.loc 1 93 1
	nop
	mov	sp, r7
.LCFI18:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI19:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
.L13:
	.align	2
.L12:
	.word	tickCount
	.cfi_endproc
.LFE122:
	.size	SysTick_Handler, .-SysTick_Handler
	.text
.Letext0:
	.file 4 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h"
	.file 5 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_stdint.h"
	.file 6 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_systick.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x33a
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0xc
	.4byte	.LASF37
	.4byte	.LASF38
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x4
	.byte	0x2b
	.byte	0x17
	.4byte	0x3c
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0x4
	.byte	0x4f
	.byte	0x1b
	.4byte	0x64
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x5
	.byte	0x18
	.byte	0x13
	.4byte	0x30
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x5
	.byte	0x30
	.byte	0x14
	.4byte	0x58
	.uleb128 0x5
	.4byte	0x93
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF13
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF14
	.uleb128 0x6
	.byte	0x4
	.byte	0x6
	.byte	0x14
	.byte	0x3
	.4byte	0x127
	.uleb128 0x7
	.ascii	"EN\000"
	.byte	0x6
	.byte	0x15
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x1
	.byte	0x1f
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF15
	.byte	0x6
	.byte	0x16
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x1
	.byte	0x1e
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF16
	.byte	0x6
	.byte	0x17
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x1
	.byte	0x1d
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x6
	.byte	0x18
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0xd
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x6
	.byte	0x19
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x6
	.byte	0x1a
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0xf
	.byte	0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x9
	.byte	0x4
	.byte	0x6
	.byte	0x10
	.byte	0x2
	.4byte	0x149
	.uleb128 0xa
	.ascii	"REG\000"
	.byte	0x6
	.byte	0x12
	.byte	0xc
	.4byte	0x93
	.uleb128 0xa
	.ascii	"BIT\000"
	.byte	0x6
	.byte	0x1b
	.byte	0x5
	.4byte	0xb2
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.byte	0x6
	.byte	0x29
	.byte	0x3
	.4byte	0x19b
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x6
	.byte	0x2a
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x18
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF21
	.byte	0x6
	.byte	0x2b
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x6
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF22
	.byte	0x6
	.byte	0x2c
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF23
	.byte	0x6
	.byte	0x2d
	.byte	0x16
	.4byte	0x9f
	.byte	0x4
	.byte	0x1
	.byte	0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x9
	.byte	0x4
	.byte	0x6
	.byte	0x25
	.byte	0x2
	.4byte	0x1bd
	.uleb128 0xa
	.ascii	"REG\000"
	.byte	0x6
	.byte	0x27
	.byte	0xc
	.4byte	0x93
	.uleb128 0xa
	.ascii	"BIT\000"
	.byte	0x6
	.byte	0x2e
	.byte	0x5
	.4byte	0x149
	.byte	0
	.uleb128 0x6
	.byte	0x10
	.byte	0x6
	.byte	0xe
	.byte	0x9
	.4byte	0x209
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x6
	.byte	0x1c
	.byte	0x4
	.4byte	0x127
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF24
	.byte	0x6
	.byte	0x1f
	.byte	0xb
	.4byte	0x93
	.byte	0x4
	.byte	0x18
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x7
	.ascii	"VAL\000"
	.byte	0x6
	.byte	0x22
	.byte	0xb
	.4byte	0x93
	.byte	0x4
	.byte	0x18
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF26
	.byte	0x6
	.byte	0x2f
	.byte	0x4
	.4byte	0x19b
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x3
	.4byte	.LASF27
	.byte	0x6
	.byte	0x30
	.byte	0x3
	.4byte	0x1bd
	.uleb128 0xc
	.4byte	.LASF39
	.byte	0x1
	.byte	0xa
	.byte	0x1a
	.4byte	0x9f
	.byte	0x5
	.byte	0x3
	.4byte	tickCount
	.uleb128 0xd
	.byte	0x1
	.4byte	.LASF40
	.byte	0x1
	.byte	0x53
	.byte	0x6
	.byte	0x1
	.4byte	.LFB122
	.4byte	.LFE122
	.4byte	.LLST3
	.byte	0x1
	.uleb128 0xe
	.byte	0x1
	.4byte	.LASF28
	.byte	0x1
	.byte	0x2b
	.byte	0x6
	.byte	0x1
	.4byte	.LFB121
	.4byte	.LFE121
	.4byte	.LLST2
	.byte	0x1
	.4byte	0x269
	.uleb128 0xf
	.4byte	.LASF30
	.byte	0x1
	.byte	0x2b
	.byte	0x1e
	.4byte	0x93
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.4byte	.LASF29
	.byte	0x1
	.byte	0x1a
	.byte	0x6
	.byte	0x1
	.4byte	.LFB120
	.4byte	.LFE120
	.4byte	.LLST1
	.byte	0x1
	.4byte	0x2fa
	.uleb128 0xf
	.4byte	.LASF31
	.byte	0x1
	.byte	0x1a
	.byte	0x21
	.4byte	0x93
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x10
	.4byte	0x315
	.4byte	.LBB22
	.4byte	.LBE22
	.byte	0x1
	.byte	0x1c
	.byte	0x2
	.4byte	0x2c8
	.uleb128 0x11
	.4byte	0x329
	.4byte	.LBB24
	.4byte	.LBE24
	.byte	0x3
	.byte	0x36
	.byte	0x2
	.uleb128 0x11
	.4byte	0x333
	.4byte	.LBB26
	.4byte	.LBE26
	.byte	0x3
	.byte	0x3a
	.byte	0x2
	.byte	0
	.uleb128 0x12
	.4byte	0x31f
	.4byte	.LBB28
	.4byte	.LBE28
	.byte	0x1
	.byte	0x22
	.byte	0x2
	.uleb128 0x11
	.4byte	0x329
	.4byte	.LBB30
	.4byte	.LBE30
	.byte	0x3
	.byte	0x2a
	.byte	0x2
	.uleb128 0x11
	.4byte	0x333
	.4byte	.LBB32
	.4byte	.LBE32
	.byte	0x3
	.byte	0x2e
	.byte	0x2
	.byte	0
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF41
	.byte	0x1
	.byte	0x10
	.byte	0xa
	.byte	0x1
	.4byte	0x93
	.4byte	.LFB119
	.4byte	.LFE119
	.4byte	.LLST0
	.byte	0x1
	.uleb128 0x14
	.4byte	.LASF32
	.byte	0x3
	.byte	0x34
	.byte	0x33
	.byte	0x1
	.byte	0x3
	.uleb128 0x14
	.4byte	.LASF33
	.byte	0x3
	.byte	0x28
	.byte	0x33
	.byte	0x1
	.byte	0x3
	.uleb128 0x14
	.4byte	.LASF34
	.byte	0x2
	.byte	0x9a
	.byte	0x33
	.byte	0x1
	.byte	0x3
	.uleb128 0x14
	.4byte	.LASF35
	.byte	0x2
	.byte	0x8f
	.byte	0x33
	.byte	0x1
	.byte	0x3
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST3:
	.4byte	.LFB122
	.4byte	.LCFI16
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI16
	.4byte	.LCFI17
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI17
	.4byte	.LCFI18
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI18
	.4byte	.LCFI19
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI19
	.4byte	.LFE122
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LFB121
	.4byte	.LCFI10
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI10
	.4byte	.LCFI11
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI11
	.4byte	.LCFI12
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI12
	.4byte	.LCFI13
	.2byte	0x2
	.byte	0x77
	.sleb128 16
	.4byte	.LCFI13
	.4byte	.LCFI14
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI14
	.4byte	.LCFI15
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI15
	.4byte	.LFE121
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LFB120
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI4
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI5
	.4byte	.LCFI6
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI6
	.4byte	.LCFI7
	.2byte	0x2
	.byte	0x77
	.sleb128 16
	.4byte	.LCFI7
	.4byte	.LCFI8
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI8
	.4byte	.LCFI9
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI9
	.4byte	.LFE120
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LFB119
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI1
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI2
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI3
	.4byte	.LFE119
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x34
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB119
	.4byte	.LFE119-.LFB119
	.4byte	.LFB120
	.4byte	.LFE120-.LFB120
	.4byte	.LFB121
	.4byte	.LFE121-.LFB121
	.4byte	.LFB122
	.4byte	.LFE122-.LFB122
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB119
	.4byte	.LFE119
	.4byte	.LFB120
	.4byte	.LFE120
	.4byte	.LFB121
	.4byte	.LFE121
	.4byte	.LFB122
	.4byte	.LFE122
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF5:
	.ascii	"__uint8_t\000"
.LASF32:
	.ascii	"SysTick_Disable\000"
.LASF31:
	.ascii	"tick_value\000"
.LASF23:
	.ascii	"NOREF\000"
.LASF41:
	.ascii	"SysTick_Get_Ticks\000"
.LASF21:
	.ascii	"reserved\000"
.LASF15:
	.ascii	"TICKINT\000"
.LASF40:
	.ascii	"SysTick_Handler\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF22:
	.ascii	"SKEW\000"
.LASF2:
	.ascii	"short int\000"
.LASF35:
	.ascii	"__enable_irq\000"
.LASF36:
	.ascii	"GNU C11 14.3.1 20250623 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -O0 -std="
	.ascii	"gnu11 -fstack-usage -fdata-sections -ffunction-sect"
	.ascii	"ions\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF18:
	.ascii	"CNTFLAG\000"
.LASF20:
	.ascii	"TENMS\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF16:
	.ascii	"CLKSRC\000"
.LASF19:
	.ascii	"reserved_2\000"
.LASF26:
	.ascii	"CALIB\000"
.LASF38:
	.ascii	"/home/shrey_shah/STM32F103C8T6/Projects/DMA/11_DMA_"
	.ascii	"Transfer/Build\000"
.LASF6:
	.ascii	"__uint32_t\000"
.LASF27:
	.ascii	"SysTick_TypeDef\000"
.LASF33:
	.ascii	"SysTick_Enable\000"
.LASF10:
	.ascii	"unsigned int\000"
.LASF37:
	.ascii	"/home/shrey_shah/STM32F103C8T6/Projects/DMA/11_DMA_"
	.ascii	"Transfer/Src/systick.c\000"
.LASF14:
	.ascii	"char\000"
.LASF11:
	.ascii	"uint8_t\000"
.LASF25:
	.ascii	"CTRL\000"
.LASF29:
	.ascii	"SysTick_Set_Ticks\000"
.LASF8:
	.ascii	"long long int\000"
.LASF30:
	.ascii	"reloadValue\000"
.LASF39:
	.ascii	"tickCount\000"
.LASF28:
	.ascii	"SysTick_Config\000"
.LASF24:
	.ascii	"LOAD\000"
.LASF34:
	.ascii	"__disable_irq\000"
.LASF4:
	.ascii	"long int\000"
.LASF17:
	.ascii	"resereved_1\000"
.LASF13:
	.ascii	"long double\000"
.LASF0:
	.ascii	"signed char\000"
.LASF12:
	.ascii	"uint32_t\000"
.LASF9:
	.ascii	"long long unsigned int\000"
	.ident	"GCC: (Arm GNU Toolchain 14.3.Rel1 (Build arm-14.174)) 14.3.1 20250623"
