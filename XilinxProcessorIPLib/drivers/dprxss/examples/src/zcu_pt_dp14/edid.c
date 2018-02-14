/******************************************************************************
*
* Copyright (C) 2018 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file edid.c
*
* This file contains edid related functions.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- --------------------------------------------------
* 1.00  Kei    10/12/17 Initial release.
* </pre>
*
******************************************************************************/

#include "xparameters.h"
#include "xdp.h"
#include "rx.h"

void edid_default()
{
	int i, j;

	// 8K30, 8K24, 5K, 4K120, 4K100 + Audio
	unsigned char edid[256] = {
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x61, 0x98, 0x23, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x28, 0x1C, 0x01, 0x04, 0xB5, 0x3C, 0x22, 0x78,
		0x26, 0x61, 0x50, 0xA6, 0x56, 0x50, 0xA0, 0x00, 0x0D, 0x50, 0x54, 0xA5,
		0x6B, 0x80, 0xD1, 0xC0, 0x81, 0xC0, 0x81, 0x00, 0x81, 0x80, 0xA9, 0x00,
		0xB3, 0x00, 0xD1, 0xFC, 0x01, 0x01, 0x04, 0x74, 0x00, 0x30, 0xF2, 0x70,
		0x5A, 0x80, 0xB0, 0x58, 0x8A, 0x00, 0x54, 0x4F, 0x21, 0x00, 0x00, 0x1A,
		0x4D, 0xD0, 0x00, 0xA0, 0xF0, 0x70, 0x3E, 0x80, 0x30, 0x20, 0x35, 0x00,
		0x56, 0x50, 0x21, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x1E,
		0x3C, 0x32, 0xB4, 0x66, 0x01, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x00, 0x00, 0x00, 0xFC, 0x00, 0x58, 0x69, 0x6C, 0x69, 0x6E, 0x78, 0x20,
		0x73, 0x69, 0x6E, 0x6B, 0x0A, 0x20, 0x01, 0x17, 0x70, 0x12, 0x6E, 0x00,
		0x00, 0x81, 0x00, 0x04, 0x23, 0x09, 0x03, 0x07, 0x03, 0x00, 0x64, 0xEB,
		0xA0, 0x01, 0x04, 0xFF, 0x0E, 0xA0, 0x00, 0x2F, 0x80, 0x21, 0x00, 0x6F,
		0x08, 0x3E, 0x00, 0x03, 0x00, 0x05, 0x00, 0xFD, 0x68, 0x01, 0x04, 0xFF,
		0x13, 0x4F, 0x00, 0x27, 0x80, 0x1F, 0x00, 0x3F, 0x0B, 0x51, 0x00, 0x43,
		0x00, 0x07, 0x00, 0x65, 0x8E, 0x01, 0x04, 0xFF, 0x1D, 0x4F, 0x00, 0x07,
		0x80, 0x1F, 0x00, 0xDF, 0x10, 0x3C, 0x00, 0x2E, 0x00, 0x07, 0x00, 0x86,
		0x3D, 0x01, 0x04, 0xFF, 0x1D, 0x4F, 0x00, 0x07, 0x80, 0x1F, 0x00, 0xDF,
		0x10, 0x30, 0x00, 0x22, 0x00, 0x07, 0x00, 0x5C, 0x7F, 0x01, 0x00, 0xFF,
		0x0E, 0x4F, 0x00, 0x07, 0x80, 0x1F, 0x00, 0x6F, 0x08, 0x73, 0x00, 0x65,
		0x00, 0x07, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x90
	};

	for (i = 0 ; i < (256 * 4) ; i = i + (16 * 4)) {
		for(j = i ; j < (i + (16 * 4)) ; j = j + 4) {
			XDp_WriteReg(VID_EDID_BASEADDR, j, edid[(i/4)+1]);
		}
	}

	for(i = 0 ; i < (256 * 4) ; i = i + 4) {
		XDp_WriteReg(VID_EDID_BASEADDR, i, edid[i/4]);
	}
}

void edid_change(int page)
{
	int i, j;
	if (page == 2) {
		xil_printf("Setting regular Dp1.2 EDID\r\n");

		unsigned char edid[256] = {
			0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
			0x61, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x0E, 0x19, 0x01, 0x04, 0xB5, 0x3C, 0x22, 0x78,
			0x3A, 0x4D, 0xD5, 0xA7, 0x55, 0x4A, 0x9D, 0x24,
			0x0E, 0x50, 0x54, 0xBF, 0xEF, 0x00, 0xD1, 0xC0,
			0x81, 0x40, 0x81, 0x80, 0x95, 0x00, 0xB3, 0x00,
			0x71, 0x4F, 0x81, 0xC0, 0x01, 0x01, 0x4D, 0xD0,
			0x00, 0xA0, 0xF0, 0x70, 0x3E, 0x80, 0x30, 0x20,
			0x35, 0x00, 0x54, 0x4F, 0x21, 0x00, 0x00, 0x1A,
			0x04, 0x74, 0x00, 0x30, 0xF2, 0x70, 0x5A, 0x80,
			0xB0, 0x58, 0x8A, 0x00, 0x54, 0x4F, 0x21, 0x00,
			0x00, 0x1A, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x1D,
			0x50, 0x18, 0xA0, 0x3C, 0x04, 0x11, 0x00, 0xF0,
			0xF8, 0x38, 0xF0, 0x3C, 0x00, 0x00, 0x00, 0xFC,
			0x00, 0x58, 0x49, 0x4C, 0x49, 0x4E, 0x58, 0x20,
			0x44, 0x50, 0x0A, 0x20, 0x20, 0x20, 0x01, 0x19,

			0x02, 0x03, 0x27, 0x71, 0x4F, 0x01, 0x02, 0x03,
			0x11, 0x12, 0x13, 0x04, 0x14, 0x05, 0x1F, 0x90,
			0x0E, 0x0F, 0x1D, 0x1E, 0x23, 0x09, 0x17, 0x07,
			0x83, 0x01, 0x00, 0x00, 0x6A, 0x03, 0x0C, 0x00,
			0x00, 0x00, 0x00, 0x78, 0x20, 0x00, 0x00, 0x56,
			0x5E, 0x00, 0xA0, 0xA0, 0xA0, 0x29, 0x50, 0x30,
			0x20, 0x35, 0x00, 0x54, 0x4F, 0x21, 0x00, 0x00,
			0x1E, 0xE2, 0x68, 0x00, 0xA0, 0xA0, 0x40, 0x2E,
			0x60, 0x30, 0x20, 0x36, 0x00, 0x54, 0x4F, 0x21,
			0x00, 0x00, 0x1A, 0x01, 0x1D, 0x00, 0xBC, 0x52,
			0xD0, 0x1E, 0x20, 0xB8, 0x28, 0x55, 0x40, 0x54,
			0x4F, 0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xD0,
			0x90, 0x20, 0x40, 0x31, 0x20, 0x0C, 0x40, 0x55,
			0x00, 0x54, 0x4F, 0x21, 0x00, 0x00, 0x18, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0
		};

		for (i = 0 ; i < (256 * 4) ; i = i + (16 * 4)) {
			for(j = i ; j < (i + (16 * 4)) ; j = j + 4) {
				XDp_WriteReg(VID_EDID_BASEADDR,
						j, edid[(i/4)+1]);
			}
		}
		for (i = 0 ; i < (256 * 4) ; i = i + 4) {
			XDp_WriteReg(VID_EDID_BASEADDR,
					i, edid[i/4]);
		}
	} else if (page == 3) {
		xil_printf("8K60 DisplayID tile setting\r\n");
		unsigned char edid[384] = {
			0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
			0x61, 0x98, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
			0x00, 0x1C, 0x01, 0x04, 0xB5, 0x46, 0x27, 0x78,
			0x3A, 0x73, 0x95, 0xAD, 0x51, 0x34, 0xB9, 0x26,
			0x0D, 0x50, 0x54, 0xA5, 0x4B, 0x00, 0x81, 0x00,
			0xB3, 0x00, 0xD1, 0x00, 0xA9, 0x40, 0x81, 0x80,
			0xD1, 0xC0, 0x01, 0x01, 0x01, 0x01, 0x4D, 0xD0,
			0x00, 0xA0, 0xF0, 0x70, 0x3E, 0x80, 0x30, 0x20,
			0x35, 0x00, 0xB9, 0x88, 0x21, 0x00, 0x00, 0x1A,
			0x00, 0x00, 0x00, 0xFF, 0x00, 0x30, 0x0A, 0x20,
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
			0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x58,
			0x69, 0x6C, 0x69, 0x6E, 0x78, 0x20, 0x38, 0x4B,
			0x36, 0x30, 0x0A, 0x20, 0x00, 0x00, 0x00, 0xFD,
			0x00, 0x18, 0x4B, 0x1E, 0xB4, 0x6C, 0x01, 0x0A,
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x02, 0x4D,

			0x02, 0x03, 0x1D, 0xF1, 0x50, 0x10, 0x1F, 0x20,
			0x05, 0x14, 0x04, 0x13, 0x12, 0x11, 0x03, 0x02,
			0x16, 0x15, 0x07, 0x06, 0x01, 0x23, 0x09, 0x1F,
			0x07, 0x83, 0x01, 0x00, 0x00, 0xA3, 0x66, 0x00,
			0xA0, 0xF0, 0x70, 0x1F, 0x80, 0x30, 0x20, 0x35,
			0x00, 0xB9, 0x88, 0x21, 0x00, 0x00, 0x1A, 0x56,
			0x5E, 0x00, 0xA0, 0xA0, 0xA0, 0x29, 0x50, 0x30,
			0x20, 0x35, 0x00, 0xB9, 0x88, 0x21, 0x00, 0x00,
			0x1A, 0x7C, 0x39, 0x00, 0xA0, 0x80, 0x38, 0x1F,
			0x40, 0x30, 0x20, 0x3A, 0x00, 0xB9, 0x88, 0x21,
			0x00, 0x00, 0x1A, 0xA8, 0x16, 0x00, 0xA0, 0x80,
			0x38, 0x13, 0x40, 0x30, 0x20, 0x3A, 0x00, 0xB9,
			0x88, 0x21, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4F,

			0x70, 0x12, 0x79, 0x00, 0x00, 0x12, 0x00, 0x16,
			0x82, 0x10, 0x00, 0x00, 0xFF, 0x0E, 0xDF, 0x10,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30,
			0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00,
			0x3C, 0x70, 0x92, 0x01, 0x84, 0xFF, 0x1D, 0x9F,
			0x00, 0x2F, 0x80, 0x1F, 0x00, 0xDF, 0x10, 0x3C,
			0x00, 0x02, 0x00, 0x04, 0x00, 0x80, 0xA0, 0x01,
			0x04, 0xFF, 0x0E, 0x9F, 0x00, 0x2F, 0x80, 0x1F,
			0x00, 0xDF, 0x10, 0x7A, 0x00, 0x02, 0x00, 0x09,
			0x00, 0x58, 0x4B, 0x01, 0x04, 0xFF, 0x0E, 0x9F,
			0x00, 0x2F, 0x80, 0x1F, 0x00, 0xDF, 0x10, 0x61,
			0x00, 0x02, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x90
		};

		for (i = 0 ; i < (384 * 4) ; i = i + (16 * 4)) {
			for(j = i ; j < (i + (16 * 4)) ; j = j + 4) {
				XDp_WriteReg(VID_EDID_BASEADDR,
						j, edid[(i/4)+1]);
			}
		}

		for(i = 0 ; i < (384 * 4) ; i = i + 4) {
			XDp_WriteReg(VID_EDID_BASEADDR,
					i, edid[i/4]);
		}

	} else if (page == 4) {
		// 8K30 only + No Audio
		xil_printf("Setting 8K30 only EDID\r\n");
		unsigned char edid[256] = {
			0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x61, 0x98, 0x23, 0x01,
			0x00, 0x00, 0x00, 0x00, 0x28, 0x1C, 0x01, 0x04, 0xA5, 0x3C, 0x22, 0x78,
			0x3E, 0x61, 0x50, 0xA6, 0x56, 0x50, 0xA0, 0x00, 0x0D, 0x50, 0x54, 0x00,
			0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
			0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0xFC, 0x00, 0x38, 0x6B, 0x33, 0x30, 0x2D, 0x6F, 0x6E,
			0x6C, 0x79, 0x0A, 0x20, 0x20, 0x20, 0x01, 0xFD, 0x70, 0x12, 0x1E, 0x00,
			0x00, 0x81, 0x00, 0x04, 0x23, 0x08, 0x1F, 0x03, 0x03, 0x00, 0x14, 0x65,
			0x8E, 0x01, 0x84, 0xFF, 0x1D, 0x4F, 0x00, 0x07, 0x80, 0x1F, 0x00, 0xDF,
			0x10, 0x3C, 0x00, 0x2E, 0x00, 0x07, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x90
		};

		for (i = 0 ; i < (256 * 4) ; i = i + (16 * 4)) {
			for (j = i ; j < (i + (16 * 4)) ; j = j + 4) {
				XDp_WriteReg(VID_EDID_BASEADDR,
						j, edid[(i/4)+1]);
			}
		}

		for(i = 0 ; i < (256 * 4) ; i = i + 4) {
			XDp_WriteReg(VID_EDID_BASEADDR,
					i, edid[i/4]);
		}
	} else if (page == 5) {
		xil_printf("Setting 4K120 EDID\r\n");
		unsigned char edid[256] = {
			0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0x00, 0x61, 0x98, 0x23, 0x01,
			0x00, 0x00, 0x00, 0x00, 0x28, 0x1C,
			0x01, 0x04, 0xB5, 0x3C, 0x22, 0x78,
			0x26, 0x61, 0x50, 0xA6, 0x56, 0x50,
			0xA0, 0x00, 0x0D, 0x50, 0x54, 0xA5,
			0x6B, 0x80, 0xD1, 0xC0, 0x81, 0xC0,
			0x81, 0x00, 0x81, 0x80, 0xA9, 0x00,
			0xB3, 0x00, 0xD1, 0xFC, 0x01, 0x01,
			0x56, 0x5E, 0x00, 0xA0, 0xA0, 0xA0,
			0x29, 0x50, 0x30, 0x00, 0x35, 0x00,
			0x56, 0x50, 0x21, 0x00, 0x00, 0x1A,
			0x4D, 0xD0, 0x00, 0xA0, 0xF0, 0x70,
			0x3E, 0x80, 0x30, 0x20, 0x35, 0x00,
			0x56, 0x50, 0x21, 0x00, 0x00, 0x1A,
			0x00, 0x00, 0x00, 0xFD, 0x00, 0x1E,
			0x3C, 0x32, 0xB4, 0x66, 0x01, 0x0A,
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
			0x00, 0x00, 0x00, 0xFC, 0x00, 0x58,
			0x69, 0x6C, 0x69, 0x6E, 0x78, 0x20,
			0x73, 0x69, 0x6E, 0x6B, 0x0A, 0x20,
			0x01, 0x18,

			0x70,
			0x12, 0x1E, 0x00,
			0x00, 0x81, 0x00, 0x04, 0x23, 0x09, 0x03, 0x07,
			0x03, 0x00,
			0x14,
			0xEB, 0xA0, 0x01,
			0x04,
			0xFF, 0x0E,
			0xA0, 0x00,
			0x2F, 0x80,
			0x21, 0x00,
			0x6F, 0x08,
			0x3E, 0x00,
			0x03, 0x00,
			0x05, 0x00,

			0x34,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x90
		};
		for (i = 0 ; i < (256 * 4) ; i = i + (16 * 4)) {
			for (j = i ; j < (i + (16 * 4)) ; j = j + 4) {
				XDp_WriteReg(VID_EDID_BASEADDR,
						j, edid[(i/4)+1]);
			}
		}
		for (i = 0 ; i < (256 * 4) ; i = i + 4) {
			XDp_WriteReg(VID_EDID_BASEADDR,
					i, edid[i/4]);
		}
	} else {
		// 8K30, 8K24, 5K, 4K120, 4K100 + Audio
		xil_printf("Setting 8K30, 8K24, 5K, 4K120, "
			   "4K100 + Audio EDID\r\n");
		unsigned char edid[256] = {
			0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0x00, 0x61, 0x98, 0x23, 0x01,
			0x00, 0x00, 0x00, 0x00, 0x28, 0x1C,
			0x01, 0x04, 0xB5, 0x3C, 0x22, 0x78,
			0x26, 0x61, 0x50, 0xA6, 0x56, 0x50,
			0xA0, 0x00, 0x0D, 0x50, 0x54, 0xA5,
			0x6B, 0x80, 0xD1, 0xC0, 0x81, 0xC0,
			0x81, 0x00, 0x81, 0x80, 0xA9, 0x00,
			0xB3, 0x00, 0xD1, 0xFC, 0x01, 0x01,
			0x04, 0x74, 0x00, 0x30, 0xF2, 0x70,
			0x5A, 0x80, 0xB0, 0x58, 0x8A, 0x00,
			0x54, 0x4F, 0x21, 0x00, 0x00, 0x1A,
			0x4D, 0xD0, 0x00, 0xA0, 0xF0, 0x70,
			0x3E, 0x80, 0x30, 0x20, 0x35, 0x00,
			0x56, 0x50, 0x21, 0x00, 0x00, 0x1A,
			0x00, 0x00, 0x00, 0xFD, 0x00, 0x1E,
			0x3C, 0x32, 0xB4, 0x66, 0x01, 0x0A,
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
			0x00, 0x00, 0x00, 0xFC, 0x00, 0x58,
			0x69, 0x6C, 0x69, 0x6E, 0x78, 0x20,
			0x73, 0x69, 0x6E, 0x6B, 0x0A, 0x20,
			0x01, 0x17, 0x70, 0x12, 0x6E, 0x00,
			0x00, 0x81, 0x00, 0x04, 0x23, 0x09,
			0x03, 0x07, 0x03, 0x00, 0x64, 0xEB,
			0xA0, 0x01, 0x04, 0xFF, 0x0E, 0xA0,
			0x00, 0x2F, 0x80, 0x21, 0x00, 0x6F,
			0x08, 0x3E, 0x00, 0x03, 0x00, 0x05,
			0x00, 0xFD, 0x68, 0x01, 0x04, 0xFF,
			0x13, 0x4F, 0x00, 0x27, 0x80, 0x1F,
			0x00, 0x3F, 0x0B, 0x51, 0x00, 0x43,
			0x00, 0x07, 0x00, 0x65, 0x8E, 0x01,
			0x04, 0xFF, 0x1D, 0x4F, 0x00, 0x07,
			0x80, 0x1F, 0x00, 0xDF, 0x10, 0x3C,
			0x00, 0x2E, 0x00, 0x07, 0x00, 0x86,
			0x3D, 0x01, 0x04, 0xFF, 0x1D, 0x4F,
			0x00, 0x07, 0x80, 0x1F, 0x00, 0xDF,
			0x10, 0x30, 0x00, 0x22, 0x00, 0x07,
			0x00, 0x5C, 0x7F, 0x01, 0x00, 0xFF,
			0x0E, 0x4F, 0x00, 0x07, 0x80, 0x1F,
			0x00, 0x6F, 0x08, 0x73, 0x00, 0x65,
			0x00, 0x07, 0x00, 0x60, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x90
		};

		for (i = 0 ; i < (256 * 4) ; i = i + (16 * 4)) {
			for (j = i ; j < (i + (16 * 4)) ; j = j + 4) {
				XDp_WriteReg(VID_EDID_BASEADDR,
						j, edid[(i/4)+1]);
			}
		}
		for (i = 0 ; i < (256 * 4) ; i = i + 4) {
			XDp_WriteReg(VID_EDID_BASEADDR,
					i, edid[i/4]);
		}
	}
}

