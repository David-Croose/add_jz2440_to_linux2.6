#include <asm/arch/hardware.h>
#include <asm/arch/virt_addr.h>

	.macro	addruart,rx
	mrc	p15, 0, \rx, c1, c0
	tst	\rx, #1				@ MMU enabled?
	ldreq \rx, =ULCON0		@ phys address
	ldrne \rx, =__ULCON0	@ virt address
	.endm

	.macro	senduart,rd,rx
	str \rd, [\rx, #0x20]	@ __UTXH0	
	.endm

	.macro	waituart,rd,rx
	.endm

	.macro	busyuart,rd,rx
1001:
	ldr \rd, [\rx, #0x10]	@ __UTRSTAT0
	tst \rd, #1 << 2
	beq 1001b
	.endm
