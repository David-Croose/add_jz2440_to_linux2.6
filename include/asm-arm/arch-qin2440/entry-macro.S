#include <asm/arch/virt_addr.h>

	.macro  disable_fiq
	.endm

	.macro  get_irqnr_preamble, base, tmp
	.endm

	.macro  arch_ret_to_user, tmp1, tmp2
	.endm

	.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp

		@@ try the interrupt offset register, since it is there

		ldr \base, =__INTPND
		ldr	\irqstat, [ \base ]
		teq	\irqstat, #0
		beq	1002f
		ldr \base, =__INTOFFSET
		ldr	\irqnr, [ \base ]
		mov	\tmp, #1
		tst	\irqstat, \tmp, lsl \irqnr
		bne	1001f

		@@ the number specified is not a valid irq, so try
		@@ and work it out for ourselves

		mov	\irqnr, #0		@@ start here

		@@ work out which irq (if any) we got

		movs	\tmp, \irqstat, lsl#16
		addeq	\irqnr, \irqnr, #16
		moveq	\irqstat, \irqstat, lsr#16
		tst	\irqstat, #0xff
		addeq	\irqnr, \irqnr, #8
		moveq	\irqstat, \irqstat, lsr#8
		tst	\irqstat, #0xf
		addeq	\irqnr, \irqnr, #4
		moveq	\irqstat, \irqstat, lsr#4
		tst	\irqstat, #0x3
		addeq	\irqnr, \irqnr, #2
		moveq	\irqstat, \irqstat, lsr#2
		tst	\irqstat, #0x1
		addeq	\irqnr, \irqnr, #1

		@@ we have the value
1001:
		adds	\irqnr, \irqnr, #0
1002:
		@@ exit here, Z flag unset if IRQ

	.endm
	

