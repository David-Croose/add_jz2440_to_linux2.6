#ifndef __QIN2440_MEMORY_H_
#define __QIN2440_MEMORY_H_

#define PHYS_OFFSET	0x30000000

#define __virt_to_bus(x) __virt_to_phys(x)
#define __bus_to_virt(x) __phys_to_virt(x)

#endif
