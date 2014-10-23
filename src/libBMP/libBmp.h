/* BMP Image Library
 * Copyright (c) <2013> <DONG HE, E-mail:hedonghust@gmail.com>
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _BMP_HEADER_
#define _BMP_HEADER_

/*define the endianess*/
/*#define TARGET_BIGENDIAN*/

#define TIGHTLY_PACKED     __declspec(align(8))
#define DWORD_PACKED       __declspec(align(32))
#define ALIGN(size, n)     ( ( ( (size) + (n)) - 1 ) & ~( (n) - 1 ) )
#ifdef TARGET_BIGENDIAN
#define SWAP32(x)          (((x&0xff000000)>>24) | \
				            ((x&0x00ff0000)>>8)  | \
				            ((x&0x0000ff00)<<8)  | \
				            ((x&0x000000ff)<<24) )
#define SWAP16(x)          (((x&0xff00)>>8)  |\
		                    ((x&0x00ff)<<8) )
#else
#define SWAP32(x)          (x)
#define SWAP16(x)          (x)
#endif

#define MALLOC             malloc
#define FREE               free

typedef unsigned char      ubyte;
typedef char               byte;
typedef unsigned short int uword;
typedef short int          word;
typedef unsigned int	   udword;

#ifdef TARGET_BIGENDIAN
#define RED_TGT            2
#define GREEN_TGT          1
#define BLUE_TGT           0
#define ALPHA_TGT          3
#else
#define RED_TGT            0
#define GREEN_TGT          1
#define BLUE_TGT           2
#define ALPHA_TGT          3
#endif

#define RED_HST            0
#define GREEN_HST          1
#define BLUE_HST           2
#define ALPHA_HST          3

typedef enum
{
	RGB24 =1,
	RGBA32,
	COMPRESSED8,
	COMPRESSED4,
	UNDEF
} pixel_format;

enum error_code
{
	SUCCESS=0,
	FAILED,
	UNKNOWN
};

typedef enum 
{
	C_NONE = 0, /*BI_RGB no compression*/
	C_8BITS, /*8 bit/pixel*/
	C_4BITS, /*4 bit/pixel*/
	/*TODO*/
}compression_code;

#pragma pack(push)
#pragma pack(2)
typedef struct  t_bitmap{
	uword	identifier;
	udword	file_size;
	udword	reserved;
	udword	data_offset;
	udword	header_size;
	udword	width;
	udword	height;
	uword	planes;
	uword	bpp;
	udword	compression;
	udword	data_size;
	udword	hresolution;
	udword	vresolution;
	udword	colors;
	udword	important_color;
	//ubyte*	pdata;
}BMPheader 
#if __GNUC__ > 3
__attribute__ ((aligned (8)))
#endif
;
#pragma pack(pop)

void writeBMP(const ubyte* rawData, int data_width, int data_height, pixel_format fmt, const char *filename);

#endif