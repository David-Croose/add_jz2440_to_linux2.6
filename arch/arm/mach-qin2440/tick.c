#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <asm-arm/mach/time.h>
#include <asm-arm/io.h>
#include <asm-arm/mach/time.h>
#include <asm/arch/clock.h>
#include <asm/arch/virt_addr.h>

static void s3c2440_timer4_init(unsigned int latch)
{
    unsigned int prescaler;    // [0,255]
    unsigned int divider;      // [2,4,8,16]
    unsigned int _divider;
    unsigned int counter;
    unsigned int tmp;

	/*
     * the timer period = ( counter / ( pclk / prescaler / divider ) ) s
     * the pclk = 50MHz
     */
	prescaler = 249;
	divider = 8;
	counter = latch;

    switch(divider)
    {
    case 2:
        _divider = 0;
        break;
    case 4:
        _divider = 1;
        break;
    case 8:
        _divider = 2;
        break;
    case 16:
        _divider = 3;
        break;
    default:
        printk("divider =%d is error, which must in [2,4,8,16] !\n", divider);
    }

	periphral_clock_enable(CLKSRC_PWMTIMER);

    tmp = __raw_readl(__TCFG0);
    tmp &= ~(0xFF << 8);
    tmp |= (prescaler & 0xFF) << 8;
	__raw_writel(tmp, __TCFG0);

    tmp = __raw_readl(__TCFG1);
    tmp &= ~(0xF << 16);
    tmp |= (_divider & 0xF) << 16;
    __raw_writel(tmp, __TCFG1);

    tmp = __raw_readl(__TCNTB4);
    tmp &= ~0xFFFF;
    tmp |= counter & 0xFFFF;
    __raw_writel(tmp, __TCNTB4);

	tmp = __raw_readl(__TCON);
    tmp &= ~(7 << 20);
	tmp |= 1 << 21;
	tmp |= 1 << 22;
	__raw_writel(tmp, __TCON);

    tmp &= ~(1 << 21);
    tmp |= 1 << 20;
	__raw_writel(tmp, __TCON);
}

static void s3c2440_timer4_enable(void)
{
    unsigned int tmp;

	tmp = __raw_readl(__INTMSK);
    tmp &= ~(1 << 14);
	__raw_writel(tmp, __INTMSK);
}

static irqreturn_t qin2440_tick_interrupt(int irq, void *dev_id)
{
	timer_tick();

	/// for debug
	/// led blinking
	{
		static unsigned int i;

		if(i < 50) {
			*(volatile unsigned int *)__GPFDAT &= ~(1 << 4);
		} else {
			*(volatile unsigned int *)__GPFDAT |= 1 << 4;
		}

		if(++i > 100) {
			i = 0;
		}
	}

	return IRQ_HANDLED;
}

static struct irqaction qin2440_tick_irq = {
	.name		= "qin2440_tick",
	.flags		= IRQF_DISABLED | IRQF_TIMER,
	.handler	= qin2440_tick_interrupt,
};

static void __init qin2440_tick_init(void)
{
	s3c2440_clock_init();
	s3c2440_timer4_init(LATCH);
	s3c2440_timer4_enable();
	setup_irq(IRQ_TIMER4, &qin2440_tick_irq);

	/// for debug
	/// led init
	{
		unsigned int tmp;

		periphral_clock_enable(CLKSRC_GPIO);

		// GPF4 set output
		tmp = *(volatile unsigned int *)__GPFCON;
		tmp &= ~((0x3 & 0x3) << (4 * 2));
		tmp |= (0x1 & 0x3) << (4 * 2);
		*(volatile unsigned int *)__GPFCON = tmp;

		*(volatile unsigned int *)__GPFDAT |= 1 << 4;
	}
}

struct sys_timer qin2440_tick = {
	.init = qin2440_tick_init,
};
