#ifndef __QIN2440_SYSTEM_H_
#define __QIN2440_SYSTEM_H_

#include <asm-arm/io.h>
#include <asm/arch/virt_addr.h>
#include <asm/arch/qin_printf.h>

void s3c24xx_default_idle(void)
{
	unsigned long tmp;
	int i;

	/* idle the system by using the idle mode which will wait for an
	 * interrupt to happen before restarting the system.
	 */

	/* Warning: going into idle state upsets jtag scanning */

	__raw_writel(__raw_readl(__CLKCON) | (1 << 2),
		     __CLKCON);

	/* the samsung port seems to do a loop and then unset idle.. */
	for (i = 0; i < 50; i++) {
		tmp += __raw_readl(__CLKCON); /* ensure loop not optimised out */
	}

	/* this bit is not cleared on re-start... */

	__raw_writel(__raw_readl(__CLKCON) & ~(1 << 2),
		     __CLKCON);
}

static inline void arch_idle(void)
{
	/// qin_printf("arch_idle\n");
	s3c24xx_default_idle();
}

static void arch_reset(char mode)
{
	qin_printf("arch_reset\n");
}

#endif
