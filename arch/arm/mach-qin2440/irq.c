#include <linux/irq.h>
#include <asm-arm/io.h>
#include <asm/arch/virt_addr.h>
#include <asm/arch/qin_printf.h>

// TODO
// there are more trigger irq to implement
static void qin2440_uart_trigger_child_irq(unsigned int irq, struct irq_desc *desc)
{
	unsigned int subsrc, submsk;

	if(irq != IRQ_UART0 && irq != IRQ_UART1 && irq != IRQ_UART2) {
		return;
	}

	subsrc = __raw_readl(__SUBSRCPND);
	submsk = __raw_readl(__INTSUBMSK);

	subsrc &= ~submsk;
	subsrc &= 0x1FF;

	// uart0
	if(subsrc & 1) {
		desc = irq_desc + IRQ_UART0_RXD;
		desc_handle_irq(IRQ_UART0_RXD, desc);
	}
	if(subsrc & (1 << 1)) {
		desc = irq_desc + IRQ_UART0_TXD;
		desc_handle_irq(IRQ_UART0_TXD, desc);
	}

	// uart1
	if(subsrc & (1 << 3)) {
		desc = irq_desc + IRQ_UART1_RXD;
		desc_handle_irq(IRQ_UART1_RXD, desc);
	}
	if(subsrc & (1 << 4)) {
		desc = irq_desc + IRQ_UART1_TXD;
		desc_handle_irq(IRQ_UART1_TXD, desc);
	}

	// uart2
	if(subsrc & (1 << 6)) {
		desc = irq_desc + IRQ_UART2_RXD;
		desc_handle_irq(IRQ_UART2_RXD, desc);
	}
	if(subsrc & (1 << 7)) {
		desc = irq_desc + IRQ_UART2_TXD;
		desc_handle_irq(IRQ_UART2_TXD, desc);
	}
}

static void qin2440_ack_irq(unsigned int irq)
{
	unsigned int _irq = irq;

	if(irq >= IRQ_EINT0 && irq <= IRQ_ADC)
	{
		__raw_writel((1 << irq), __SRCPND);
		__raw_writel((1 << irq), __INTPND);
	}

	if(irq >= IRQ_EINT4 && irq <= IRQ_EINT23) {
		_irq = irq - 47;
		__raw_writel((1 << _irq), __EINTPEND);

		// clear the parent irq pending bit
		{
			if(irq >= IRQ_EINT4 && irq <= IRQ_EINT7) {
				__raw_writel((1 << IRQ_EINT4_7), __SRCPND);
				__raw_writel((1 << IRQ_EINT4_7), __INTPND);
			}

			if(irq >= IRQ_EINT8 && irq <= IRQ_EINT23) {
				__raw_writel((1 << IRQ_EINT8_23), __SRCPND);
				__raw_writel((1 << IRQ_EINT8_23), __INTPND);
			}
		}
	}

	if(irq >= IRQ_UART0_RXD && irq <= IRQ_WDT_AC97_AC97) {
		_irq = irq - 32;
		__raw_writel((1 << _irq), __SUBSRCPND);

		// clear the parent irq pending bit
		{
			if(irq >= IRQ_UART0_RXD && irq <= IRQ_UART0_ERR) {
				__raw_writel((1 << IRQ_UART0), __SRCPND);
				__raw_writel((1 << IRQ_UART0), __INTPND);
			}

			if(irq >= IRQ_UART1_RXD && irq <= IRQ_UART1_ERR) {
				__raw_writel((1 << IRQ_UART1), __SRCPND);
				__raw_writel((1 << IRQ_UART1), __INTPND);
			}

			if(irq >= IRQ_UART2_RXD && irq <= IRQ_UART2_ERR) {
				__raw_writel((1 << IRQ_UART2), __SRCPND);
				__raw_writel((1 << IRQ_UART2), __INTPND);
			}

			if(irq == IRQ_ADC_TC || irq == IRQ_ADC_S) {
				__raw_writel((1 << IRQ_ADC), __SRCPND);
				__raw_writel((1 << IRQ_ADC), __INTPND);
			}

			if(irq == IRQ_CAM_P || irq == IRQ_CAM_C) {
				__raw_writel((1 << IRQ_INT_CAM), __SRCPND);
				__raw_writel((1 << IRQ_INT_CAM), __INTPND);
			}

			if(irq == IRQ_WDT_AC97_AC97 || irq == IRQ_WDT_AC97_WDT) {
				__raw_writel((1 << IRQ_WDT_AC97), __SRCPND);
				__raw_writel((1 << IRQ_WDT_AC97), __INTPND);
			}
		}
	}
}

static void qin2440_mask_irq(unsigned int irq)
{
	unsigned int tmp;
	unsigned int _irq;

	if(irq >= IRQ_EINT0 && irq <= IRQ_ADC) {
		tmp = __raw_readl(__INTMSK);
		tmp |= (1 << irq);
		__raw_writel(tmp, __INTMSK);
	}

	if(irq >= IRQ_EINT4 && irq <= IRQ_EINT23) {
		_irq = irq - 47;
		tmp = __raw_readl(__EINTMASK);
		tmp |= 1 << _irq;
		__raw_writel(tmp, __EINTMASK);
	}

	if(irq >= IRQ_UART0_RXD && irq <= IRQ_WDT_AC97_AC97) {
		_irq = irq - 32;
		tmp = __raw_readl(__INTSUBMSK);
		tmp |= 1 << _irq;
		__raw_writel(tmp, __INTSUBMSK);
	}
}

static void qin2440_unmask_irq(unsigned int irq)
{
	unsigned int tmp;
	unsigned int _irq;

	if(irq >= IRQ_EINT0 && irq <= IRQ_ADC) {
		tmp = __raw_readl(__INTMSK);
		tmp &= ~(1 << irq);
		__raw_writel(tmp, __INTMSK);
	}

	if(irq >= IRQ_EINT4 && irq <= IRQ_EINT23) {
		_irq = irq - 47;
		tmp = __raw_readl(__EINTMASK);
		tmp &= ~(1 << _irq);
		__raw_writel(tmp, __EINTMASK);
	}

	if(irq >= IRQ_UART0_RXD && irq <= IRQ_WDT_AC97_AC97) {
		_irq = irq - 32;
		tmp = __raw_readl(__INTSUBMSK);
		tmp &= ~(1 << _irq);
		__raw_writel(tmp, __INTSUBMSK);
	}
}

static struct irq_chip qin2440_irq_chip = {
	.name	= "qin2440_parent_irq",
	.ack	= qin2440_ack_irq,
	.mask	= qin2440_mask_irq,
	.unmask	= qin2440_unmask_irq,
};

static struct irq_chip qin2440_irq_chip_2 = {
	.name	= "qin2440_children_irq",
	.ack	= qin2440_ack_irq,
	.mask	= qin2440_mask_irq,
	.unmask	= qin2440_unmask_irq,
};

void __init qin2440_init_irq(void)
{
	int i;

	/* make sure the irq pending bits clear out */
	for(i = 0; i < 3; i++) {
		__raw_writel(__raw_readl(__SUBSRCPND), __SUBSRCPND);
		__raw_writel(__raw_readl(__SRCPND),    __SRCPND);
		__raw_writel(__raw_readl(__INTPND),    __INTPND);
		__raw_writel(__raw_readl(__EINTPEND),  __EINTPEND);
	}

	// the tiemr4 is for linux tick
	{
		set_irq_chip_and_handler(IRQ_TIMER4, &qin2440_irq_chip, handle_level_irq);
		set_irq_flags(IRQ_TIMER4, IRQF_VALID);
	}

	// the uart0
	{
		set_irq_chip(IRQ_UART0, &qin2440_irq_chip);
		set_irq_chained_handler(IRQ_UART0, qin2440_uart_trigger_child_irq);

		set_irq_chip_and_handler(IRQ_UART0_TXD, &qin2440_irq_chip_2, handle_level_irq);
		set_irq_flags(IRQ_UART0_TXD, IRQF_VALID);

		set_irq_chip_and_handler(IRQ_UART0_RXD, &qin2440_irq_chip_2, handle_level_irq);
		set_irq_flags(IRQ_UART0_RXD, IRQF_VALID);
	}

	// the uart1
	{
		set_irq_chip(IRQ_UART1, &qin2440_irq_chip);
		set_irq_chained_handler(IRQ_UART1, qin2440_uart_trigger_child_irq);

		set_irq_chip_and_handler(IRQ_UART1_TXD, &qin2440_irq_chip_2, handle_level_irq);
		set_irq_flags(IRQ_UART1_TXD, IRQF_VALID);

		set_irq_chip_and_handler(IRQ_UART1_RXD, &qin2440_irq_chip_2, handle_level_irq);
		set_irq_flags(IRQ_UART1_RXD, IRQF_VALID);
	}

	// the uart2
	{
		set_irq_chip(IRQ_UART2, &qin2440_irq_chip);
		set_irq_chained_handler(IRQ_UART2, qin2440_uart_trigger_child_irq);

		set_irq_chip_and_handler(IRQ_UART2_TXD, &qin2440_irq_chip_2, handle_level_irq);
		set_irq_flags(IRQ_UART2_TXD, IRQF_VALID);

		set_irq_chip_and_handler(IRQ_UART2_RXD, &qin2440_irq_chip_2, handle_level_irq);
		set_irq_flags(IRQ_UART2_RXD, IRQF_VALID);
	}
}
