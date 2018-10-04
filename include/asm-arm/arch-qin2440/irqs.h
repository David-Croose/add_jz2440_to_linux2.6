#ifndef __QIN2440_IRQS_H_
#define __QIN2440_IRQS_H_

/*
 * parent irq
 *
 * note that if a parent irq has child irq, it
 * can not be requested
 */
#define IRQ_ADC           31   /* can't be requested */
#define IRQ_RTC           30
#define IRQ_SPI1          29
#define IRQ_UART0         28   /* can't be requested */
#define IRQ_IIC           27
#define IRQ_USBH          26
#define IRQ_USBD          25
#define IRQ_NFCON         24
#define IRQ_UART1         23   /* can't be requested */
#define IRQ_SPI0          22
#define IRQ_SDI           21
#define IRQ_DMA3          20
#define IRQ_DMA2          19
#define IRQ_DMA1          18
#define IRQ_DMA0          17
#define IRQ_LCD           16
#define IRQ_UART2         15   /* can't be requested */
#define IRQ_TIMER4        14
#define IRQ_TIMER3        13
#define IRQ_TIMER2        12
#define IRQ_TIMER1        11
#define IRQ_TIMER0        10
#define IRQ_WDT_AC97      9    /* can't be requested */
#define IRQ_TICK          8
#define IRQ_BATT_FLT      7
#define IRQ_INT_CAM       6    /* can't be requested */
#define IRQ_EINT8_23      5    /* can't be requested */
#define IRQ_EINT4_7       4    /* can't be requested */
#define IRQ_EINT3         3
#define IRQ_EINT2         2
#define IRQ_EINT1         1
#define IRQ_EINT0         0

/*
 * child irq
 */
#define IRQ_WDT_AC97_AC97 (32 + 14)
#define IRQ_WDT_AC97_WDT  (32 + 13)
#define IRQ_CAM_P         (32 + 12)
#define IRQ_CAM_C         (32 + 11)
#define IRQ_ADC_S         (32 + 10)
#define IRQ_ADC_TC        (32 + 9)
#define IRQ_UART2_ERR     (32 + 8)
#define IRQ_UART2_TXD     (32 + 7)
#define IRQ_UART2_RXD     (32 + 6)
#define IRQ_UART1_ERR     (32 + 5)
#define IRQ_UART1_TXD     (32 + 4)
#define IRQ_UART1_RXD     (32 + 3)
#define IRQ_UART0_ERR     (32 + 2)
#define IRQ_UART0_TXD     (32 + 1)
#define IRQ_UART0_RXD     (32 + 0)

#define IRQ_EINT23        (47 + 23)
#define IRQ_EINT22        (47 + 22)
#define IRQ_EINT21        (47 + 21)
#define IRQ_EINT20        (47 + 20)
#define IRQ_EINT19        (47 + 19)
#define IRQ_EINT18        (47 + 18)
#define IRQ_EINT17        (47 + 17)
#define IRQ_EINT16        (47 + 16)
#define IRQ_EINT15        (47 + 15)
#define IRQ_EINT14        (47 + 14)
#define IRQ_EINT13        (47 + 13)
#define IRQ_EINT12        (47 + 12)
#define IRQ_EINT11        (47 + 11)
#define IRQ_EINT10        (47 + 10)
#define IRQ_EINT9         (47 + 9)
#define IRQ_EINT8         (47 + 8)
#define IRQ_EINT7         (47 + 7)
#define IRQ_EINT6         (47 + 6)
#define IRQ_EINT5         (47 + 5)
#define IRQ_EINT4         (47 + 4)

#define NR_IRQS			  (IRQ_EINT23 - IRQ_EINT0 + 1)

#endif
