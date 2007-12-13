/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 *   Copyright (C) 2005 infineon
 *   Copyright (C) 2007 John Crispin <blogic@openwrt.org> 
 *
 */

#ifndef DANUBE_WDT_H
#define DANUBE_WDT_H

/* Danube wdt ioctl control */
#define DANUBE_WDT_IOC_MAGIC			0xc0
#define DANUBE_WDT_IOC_START			_IOW(DANUBE_WDT_IOC_MAGIC, 0, int)
#define DANUBE_WDT_IOC_STOP				_IO(DANUBE_WDT_IOC_MAGIC, 1)
#define DANUBE_WDT_IOC_PING				_IO(DANUBE_WDT_IOC_MAGIC, 2)
#define DANUBE_WDT_IOC_SET_PWL			_IOW(DANUBE_WDT_IOC_MAGIC, 3, int)
#define DANUBE_WDT_IOC_SET_DSEN			_IOW(DANUBE_WDT_IOC_MAGIC, 4, int)
#define DANUBE_WDT_IOC_SET_LPEN			_IOW(DANUBE_WDT_IOC_MAGIC, 5, int)
#define DANUBE_WDT_IOC_GET_STATUS		_IOR(DANUBE_WDT_IOC_MAGIC, 6, int)
#define DANUBE_WDT_IOC_SET_CLKDIV		_IOW(DANUBE_WDT_IOC_MAGIC, 7, int)

/* password 1 and 2 */
#define DANUBE_WDT_PW1					 0x000000BE
#define DANUBE_WDT_PW2					 0x000000DC

#define DANUBE_WDT_CLKDIV0_VAL			1
#define DANUBE_WDT_CLKDIV1_VAL			64
#define DANUBE_WDT_CLKDIV2_VAL			4096
#define DANUBE_WDT_CLKDIV3_VAL			262144
#define DANUBE_WDT_CLKDIV0				0
#define DANUBE_WDT_CLKDIV1				1
#define DANUBE_WDT_CLKDIV2				2
#define DANUBE_WDT_CLKDIV3				3

#endif