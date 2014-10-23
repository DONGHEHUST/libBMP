#include "libBmp.h"
#include <stdio.h>
#include <stdlib.h>

#define x 16
#define y 16

void main(){
	ubyte *p = MALLOC(4*x*y);
	int i,j;
	unsigned int *ptr = (unsigned int*)p;
	for(i=0; i<x; i++){
		for(j=0; j<y; j++){
			unsigned int val = (ubyte)((i)*(j));
			*ptr = (0xff<<24) | (val<<16) | (val<<8) | val;
			ptr++;
		}
	}
	writeBMP(p, x, y, RGBA32, "test_grey.bmp");
	
	ptr = (unsigned int*)p;
	for(i=0; i<x; i++){
		for(j=0; j<y; j++){
			unsigned int val = (ubyte)((i)*(j));
			*ptr = (0xff<<24) | (val<<16);
			ptr++;
		}
	}
	writeBMP(p, x, y, RGBA32, "test_red.bmp");

}