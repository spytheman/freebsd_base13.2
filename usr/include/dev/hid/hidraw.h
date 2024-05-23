/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2020 Vladimir Kondratyev <wulf@FreeBSD.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _HID_HIDRAW_H
#define _HID_HIDRAW_H

#include <sys/ioccom.h>

#define	HIDRAW_BUFFER_SIZE	64	/* number of input reports buffered */
#define	HID_MAX_DESCRIPTOR_SIZE	4096	/* artificial limit taken from Linux */

/*
 * Align IOCTL structures to hide differences when running 32-bit
 * programs under 64-bit kernels:
 */
#ifdef COMPAT_32BIT
#define	HIDRAW_IOCTL_STRUCT_ALIGN(n) __aligned(n)
#else
#define	HIDRAW_IOCTL_STRUCT_ALIGN(n)
#endif

/* Compatible with usb_gen_descriptor structure */
struct hidraw_gen_descriptor {
#ifdef COMPAT_32BIT
	uint64_t hgd_data;
#else
	void   *hgd_data;
#endif
	uint16_t hgd_lang_id;
	uint16_t hgd_maxlen;
	uint16_t hgd_actlen;
	uint16_t hgd_offset;
	uint8_t hgd_config_index;
	uint8_t hgd_string_index;
	uint8_t hgd_iface_index;
	uint8_t hgd_altif_index;
	uint8_t hgd_endpt_index;
	uint8_t hgd_report_type;
	uint8_t reserved[8];
} HIDRAW_IOCTL_STRUCT_ALIGN(8);

struct hidraw_report_descriptor {
	uint32_t	size;
	uint8_t		value[HID_MAX_DESCRIPTOR_SIZE];
} HIDRAW_IOCTL_STRUCT_ALIGN(4);

struct hidraw_devinfo {
	uint32_t	bustype;
	int16_t		vendor;
	int16_t		product;
} HIDRAW_IOCTL_STRUCT_ALIGN(4);

/* FreeBSD uhid(4)-compatible ioctl interface */
#define	HIDRAW_GET_REPORT_DESC	_IOWR('U', 21, struct hidraw_gen_descriptor)
#define	HIDRAW_SET_IMMED	_IOW ('U', 22, int)
#define	HIDRAW_GET_REPORT	_IOWR('U', 23, struct hidraw_gen_descriptor)
#define	HIDRAW_SET_REPORT	_IOW ('U', 24, struct hidraw_gen_descriptor)
#define	HIDRAW_GET_REPORT_ID	_IOR ('U', 25, int)
#define	HIDRAW_SET_REPORT_DESC	_IOW ('U', 26, struct hidraw_gen_descriptor)

/* Linux hidraw-compatible ioctl interface */
#define	HIDIOCGRDESCSIZE	_IOR('U', 30, int)
#define	HIDIOCGRDESC		_IO ('U', 31)
#define	HIDIOCGRAWINFO		_IOR('U', 32, struct hidraw_devinfo)
#define	HIDIOCGRAWNAME(len)	_IOC(IOC_OUT,   'U', 33, len)
#define	HIDIOCGRAWPHYS(len)	_IOC(IOC_OUT,   'U', 34, len)
#define	HIDIOCSFEATURE(len)	_IOC(IOC_IN,    'U', 35, len)
#define	HIDIOCGFEATURE(len)	_IOC(IOC_INOUT, 'U', 36, len)
#define	HIDIOCGRAWUNIQ(len)	_IOC(IOC_OUT,   'U', 37, len)

#endif	/* _HID_HIDRAW_H */
