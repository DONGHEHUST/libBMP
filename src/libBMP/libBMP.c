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

#include "libBmp.h"
#include <stdio.h>
#include <stdlib.h>

static BMPheader header;

void writeBMP(const ubyte* rawData, int data_width, int data_height, pixel_format fmt, const char *filename)
{
	int pixel_data_size, i, j;
	ubyte *bmpData = NULL;
	FILE *file = fopen(filename, "wb");
	
	if(NULL == file){
		return;
	}

	/*assume the rawData are always in format ARGB32*/
	if(fmt == RGB24)
	{
		int stride = ALIGN((data_width*3), 4);
		pixel_data_size = stride*data_height;
		header.identifier = SWAP16(0x4d42);/*Identifier*/
		header.file_size = SWAP32(0x36 + pixel_data_size);
		header.reserved = 0x0;
		header.data_offset = SWAP32(0x36);
		header.header_size = SWAP32(0x28);
		header.width = SWAP32(data_width);
		header.height = SWAP32(data_height);
		header.planes = 0;
		header.bpp = SWAP16(24);
		header.compression =C_NONE;
		header.data_size = SWAP32(pixel_data_size);
		header.hresolution = 0;
		header.vresolution = 0;
		header.colors = 0;
		header.important_color = 0;
		bmpData = (ubyte*)MALLOC(pixel_data_size);
		/*copy data*/
		for(i=0; i<data_height; i++){
			for(j=0; j<data_width; j++){
				bmpData[i*stride + j*4 + RED_HST]   = rawData[i*data_width*4 + j*4 + RED_TGT];
				bmpData[i*stride + j*4 + GREEN_HST] = rawData[i*data_width*4 + j*4 + GREEN_TGT];
				bmpData[i*stride + j*4 + BLUE_HST]  = rawData[i*data_width*4 + j*4 + BLUE_TGT];
			}
		}
	}
	else if( fmt == RGBA32)
	{
		int stride =  data_width*4;
		pixel_data_size = stride*data_height;
		header.identifier = SWAP16(0x4d42);/*BM*/
		header.file_size = SWAP32(0x36 + pixel_data_size);
		header.reserved = 0x0;
		header.data_offset = SWAP32(0x36);
		header.header_size = SWAP32(0x28);
		header.width = SWAP32(data_width);
		header.height = SWAP32(data_height);
		header.planes = 0;
		header.bpp = SWAP16(32);
		header.compression = C_NONE;
		header.data_size = SWAP32(pixel_data_size);
		header.hresolution = 0;
		header.vresolution = 0;
		header.colors = 0;
		header.important_color = 0;
		bmpData = (ubyte*)MALLOC(pixel_data_size);
		/*copy data*/
		for(i=0; i<data_height; i++){
			for(j=0; j<data_width; j++){
				bmpData[i*stride + j*4 + RED_HST]   = rawData[i*data_width*4 + j*4 + RED_TGT];
				bmpData[i*stride + j*4 + GREEN_HST] = rawData[i*data_width*4 + j*4 + GREEN_TGT];
				bmpData[i*stride + j*4 + BLUE_HST]  = rawData[i*data_width*4 + j*4 + BLUE_TGT];
				bmpData[i*stride + j*4 + ALPHA_HST] = rawData[i*data_width*4 + j*4 + ALPHA_TGT];
			}
		}
	}
	
	/*write bmp*/
	fwrite(&header, 1, sizeof(header), file);
	fwrite(bmpData, 1, pixel_data_size, file);
	fclose(file);

	FREE(bmpData);
}
