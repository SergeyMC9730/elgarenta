#include <stdio.h>
#include "bmp.h"
#include <assert.h>
#include <stdlib.h>

#define GET_INDEX(x, y, w) w * x + y

BMPImage *openBMP(const char *filename) {
	BMPImage *img = (BMPImage *)malloc(sizeof(BMPImage));
	FILE *bFile = fopen(filename, "rb");
	assert(bFile);
	assert(img);

	fread(img, sizeof(BMPHeader), 1, bFile);

	img->data = (char *)malloc(img->header.size);

	fread(img->data, img->header.size, 1, bFile);
	fclose(bFile);

	img->data += 84;

	// convert to rgb from bgr

	int i = 0;
	while(i < img->header.size - 84) {
		char a = img->data[i + 0];
		img->data[i + 0] = img->data[i + 2];
		img->data[i + 2] = a;
		i += 3;
	}

	// rotate

	// i = 0;
	// char *new_data = (char *)malloc(img->header.size);
	// while(i < img->header.width_px) {
	// 	int ii = 0;
	// 	while(ii < img->header.height_px) {
	// 		new_data[GET_INDEX(img->header.width_px - 1, ii, img->header.width_px)] = img->data[GET_INDEX(i, ii, img->header.width_px)];
	// 		ii++;
	// 	}
	// 	i++;
	// }

	// free(img->data - 84);
	// img->data = new_data;

	return img;
}

