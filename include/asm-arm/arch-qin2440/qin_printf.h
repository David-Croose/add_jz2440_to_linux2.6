#ifndef _QIN_DEBUG_H_
#define _QIN_DEBUG_H_

#ifdef CONFIG_QIN_PRINTF
extern int qin_printf(const char *, ...);
#else
#define qin_printf(x...)
#endif

#endif
