# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=mips
BOARD:=brcm63xx
BOARDNAME:=Broadcom BCM63xx
FEATURES:=squashfs jffs2 broken usb atm
LINUX_VERSION:=2.6.27.4

include $(INCLUDE_DIR)/target.mk

define Target/Description
	Build firmware images for Broadcom based xDSL/routers
	currently supports BCM6348 and BCM6358 based devices.
	(e.g. Inventel Livebox, Siemens SE515)
endef

$(eval $(call BuildTarget))
