/*****************************************************************************
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2003 ADMtek Incorporated.
 *	daniell@admtek.com.tw
 *
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 *****************************************************************************/

#include <linux/init.h>
#include <linux/autoconf.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/bootmem.h>

#include <asm/bootinfo.h>
#include <asm/addrspace.h>

/* boot loaders specific definitions */
#define CFE_EPTSEAL 0x43464531 /* CFE1 is the magic number to recognize CFE from other bootloaders */
#define CFE 1
#define UBOOT 2
#define MYLOADER 3
#define UNKNOWN 0

void setup_prom_printf(int);
void prom_printf(char *, ...);
void prom_meminit(void);

/* we assume we don't know the boot loader by default */
int boot_loader_type = UNKNOWN;

#define ADM5120_ENVC           1

char *adm5120_envp[2*ADM5120_ENVC] = {"memsize","0x001000000"};

#define READCSR(r)      *(volatile unsigned long *)(0xB2600000+(r))
#define WRITECSR(r,v)   *(volatile unsigned long *)(0xB2600000+(r)) = v

#define UART_DR_REG         0x00
#define UART_FR_REG         0x18
#define UART_TX_FIFO_FULL   0x20

int putPromChar(char c)
{
	WRITECSR(UART_DR_REG, c);
        while ( (READCSR(UART_FR_REG) & UART_TX_FIFO_FULL) );
        return 0;
}

/*
 * Ugly prom_printf used for debugging
 */

void prom_printf(char *fmt, ...)
{
        va_list args;
        int l;
        char *p, *buf_end;
        char buf[1024];

        va_start(args, fmt);
        l = vsprintf(buf, fmt, args); /* hopefully i < sizeof(buf) */
        va_end(args);

        buf_end = buf + l;

        for (p = buf; p < buf_end; p++) {
                /* Crude cr/nl handling is better than none */
                if (*p == '\n')
                        putPromChar('\r');
                putPromChar(*p);
        }
}

char *prom_getenv(char *envname)
{
	int i, index=0;

	i = strlen(envname);

	printk(KERN_INFO "GETENV: envname is %s\n", envname);

	while(index < (2*ADM5120_ENVC)) {
		if(strncmp(envname, adm5120_envp[index], i) == 0) {
			printk(KERN_INFO "GETENV: returning %s\n", adm5120_envp[index+1]);
			return(adm5120_envp[index+1]);
		}
		index += 2;
	}

	printk(KERN_INFO "GETENV: not found.\n");
	return(NULL);
}
	
/*
 * initialize the prom module.
 */
void __init prom_init(void)
{
	/* you should these macros defined in include/asm/bootinfo.h */
	mips_machgroup = MACH_GROUP_ADM_GW;
	mips_machtype = MACH_ADM_GW_5120;

	/* init command line, register a default kernel command line */
	strcpy(&(arcs_cmdline[0]), "console=ttyS0,115200 rootfstype=squashfs,jffs2 init=/etc/preinit");

	/* check for CFE by finding the CFE magic number */
	int *prom_vec = (int *) fw_arg3;
	int argc = fw_arg0;
	unsigned int cfe_eptseal;

	if (argc < 0)
		cfe_eptseal = (uint32_t)(unsigned long)prom_vec;
	else {
		if ((int32_t)(long)prom_vec < 0)
			 /*
			  * Old loaders all it gives us is the handle,
			  * so assume the seal.
			  */
			cfe_eptseal = CFE_EPTSEAL;
		else
			/*
			 * Newer loaders bundle the handle/ept/eptseal
			 */
			cfe_eptseal = (unsigned int)((uint32_t *)prom_vec)[3];
	}
	if (cfe_eptseal == CFE_EPTSEAL) {
		boot_loader_type = CFE;
		printk("adm5120 : CFE boot loader\n");
	}

	/* init memory map */
	prom_meminit();
}
