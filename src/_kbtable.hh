/* _kbtable.hh -- key tables
 * Copyright (C) 1995-1998 Markus F.X.J. Oberhumer
 * For conditions of distribution and use, see copyright notice in kb.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the keyboard library and is
   subject to change. Applications should only use kb.h.
 */


/* DO NOT EDIT - this file is automatically generated */


const unsigned char _kb_prefix_scancode [ 128 ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x60, 0x61, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x78, 0x63,
	0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x65, 0x66,
	0x67, 0x68, 0x00, 0x69, 0x00, 0x6a, 0x00, 0x6b,
	0x6c, 0x6d, 0x6e, 0x6f, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7d, 0x7e, 0x7f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned short _kb_shift_state_table [ 128 ] = {
	0x6000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4004, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x4001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4002, 0x0000,
	0x4010, 0x0000, 0x4040, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4080, 0x4100, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x4000, 0x6000, 0x0000, 0x0000,
	0x0000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000,
	0x0000, 0x4008, 0x0000, 0x0000, 0x4020, 0xc800, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0200, 0x0000,
	0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0xc400,
	0xc000, 0x6000, 0x6000, 0x6000, 0x6000, 0x4000, 0x4000, 0x4000
};

static const unsigned short default_plain_table [ 128 ] = {
	0x0000, 0x001b, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036,
	0x0037, 0x0038, 0x0039, 0x0030, 0x002d, 0x003d, 0x0008, 0x0009,
	0x0071, 0x0077, 0x0065, 0x0072, 0x0074, 0x0079, 0x0075, 0x0069,
	0x006f, 0x0070, 0x005b, 0x005d, 0x000d, 0x0000, 0x0061, 0x0073,
	0x0064, 0x0066, 0x0067, 0x0068, 0x006a, 0x006b, 0x006c, 0x003b,
	0x0027, 0x0060, 0x0000, 0x005c, 0x007a, 0x0078, 0x0063, 0x0076,
	0x0062, 0x006e, 0x006d, 0x002c, 0x002e, 0x002f, 0x0000, 0x002a,
	0x0000, 0x0020, 0x0000, 0x013b, 0x013c, 0x013d, 0x013e, 0x013f,
	0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0000, 0x0000, 0x0037,
	0x0038, 0x0039, 0x002d, 0x0034, 0x0035, 0x0036, 0x002b, 0x0031,
	0x0032, 0x0033, 0x0030, 0x002e, 0x0000, 0x0000, 0x005c, 0x0185,
	0x0186, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x000d, 0x0000, 0x002f, 0x0000, 0x0000, 0x0000, 0x0247, 0x0248,
	0x0249, 0x024b, 0x024d, 0x024f, 0x0250, 0x0251, 0x0252, 0x0253,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

static const unsigned short default_shift_table [ 128 ] = {
	0x0000, 0x001b, 0x0021, 0x0040, 0x0023, 0x0024, 0x0025, 0x005e,
	0x0026, 0x002a, 0x0028, 0x0029, 0x005f, 0x002b, 0x0008, 0x010f,
	0x0051, 0x0057, 0x0045, 0x0052, 0x0054, 0x0059, 0x0055, 0x0049,
	0x004f, 0x0050, 0x007b, 0x007d, 0x000d, 0x0000, 0x0041, 0x0053,
	0x0044, 0x0046, 0x0047, 0x0048, 0x004a, 0x004b, 0x004c, 0x003a,
	0x0022, 0x007e, 0x0000, 0x007c, 0x005a, 0x0058, 0x0043, 0x0056,
	0x0042, 0x004e, 0x004d, 0x003c, 0x003e, 0x003f, 0x0000, 0x002a,
	0x0000, 0x0020, 0x0000, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158,
	0x0159, 0x015a, 0x015b, 0x015c, 0x015d, 0x0000, 0x0000, 0x0037,
	0x0038, 0x0039, 0x002d, 0x0034, 0x0035, 0x0036, 0x002b, 0x0031,
	0x0032, 0x0033, 0x0030, 0x002e, 0x0000, 0x0000, 0x007c, 0x0187,
	0x0188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x000d, 0x0000, 0x002f, 0x0000, 0x0000, 0x0000, 0x0247, 0x0248,
	0x0249, 0x024b, 0x024d, 0x024f, 0x0250, 0x0251, 0x0252, 0x0253,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

static const unsigned short default_control_table [ 128 ] = {
	0x0000, 0x001b, 0x0000, 0x0103, 0x0000, 0x0000, 0x0000, 0x001e,
	0x0000, 0x0000, 0x0000, 0x0000, 0x001c, 0x0000, 0x007f, 0x0194,
	0x0011, 0x0017, 0x0005, 0x0012, 0x0014, 0x0019, 0x0015, 0x0009,
	0x000f, 0x0010, 0x001b, 0x001d, 0x000a, 0x0000, 0x0001, 0x0013,
	0x0004, 0x0006, 0x0007, 0x0008, 0x000a, 0x000b, 0x000c, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x001a, 0x0018, 0x0003, 0x0016,
	0x0002, 0x000e, 0x000d, 0x0000, 0x0000, 0x001f, 0x0000, 0x0196,
	0x0000, 0x0020, 0x0000, 0x015e, 0x015f, 0x0160, 0x0161, 0x0162,
	0x0163, 0x0164, 0x0165, 0x0166, 0x0167, 0x0000, 0x0000, 0x0177,
	0x018d, 0x0184, 0x018e, 0x0173, 0x018f, 0x0174, 0x0190, 0x0175,
	0x0191, 0x0176, 0x0192, 0x0193, 0x0000, 0x0000, 0x0000, 0x0189,
	0x018a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x000a, 0x0000, 0x0195, 0x0172, 0x0000, 0x0000, 0x0277, 0x028d,
	0x0284, 0x0273, 0x0274, 0x0275, 0x0291, 0x0276, 0x0292, 0x0293,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

static const unsigned short default_alt_table [ 128 ] = {
	0x0000, 0x0101, 0x0178, 0x0179, 0x017a, 0x017b, 0x017c, 0x017d,
	0x017e, 0x017f, 0x0180, 0x0181, 0x0182, 0x0183, 0x010e, 0x01a5,
	0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117,
	0x0118, 0x0119, 0x011a, 0x011b, 0x011c, 0x0000, 0x011e, 0x011f,
	0x0120, 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127,
	0x0128, 0x0129, 0x0000, 0x012b, 0x012c, 0x012d, 0x012e, 0x012f,
	0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x0135, 0x0000, 0x0137,
	0x0000, 0x0020, 0x0000, 0x0168, 0x0169, 0x016a, 0x016b, 0x016c,
	0x016d, 0x016e, 0x016f, 0x0170, 0x0171, 0x0000, 0x0000, 0x0297,
	0x0298, 0x0299, 0x014a, 0x029b, 0x029c, 0x029d, 0x014e, 0x029f,
	0x02a0, 0x02a1, 0x02a2, 0x02a3, 0x0000, 0x0000, 0x0000, 0x018b,
	0x018c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x01a6, 0x0000, 0x01a4, 0x0000, 0x0000, 0x0000, 0x0197, 0x0198,
	0x0199, 0x019b, 0x019d, 0x019f, 0x01a0, 0x01a1, 0x01a2, 0x01a3,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};


/*
vi:ts=4
*/
