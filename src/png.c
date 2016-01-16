/*
 * png.c
 *
 *  Created on: Jan 7, 2016
 *      Author: os
 */

#include "image.h"
#include <libpng/png.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int read_png(const char *filepath, struct image *img);


int read_image(const char *file_path, struct image *img){

	/* TODO:
	 	 	 classify file here */

	return read_png(file_path, img);
}


int read_png(const char *filepath, struct image *img){

	FILE *png_file = fopen(filepath, "rb");
	if(!png_file){

		MESSAGE("png_file == NULL");

		return -1;
	}

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png){

		MESSAGE("png_struct wasn't readed!");
		return -1;
	}

	png_infop info = png_create_info_struct(png);
	if(!info){

		MESSAGE("cannot read png_infop struct!");
		return -1;
	}

	if(setjmp(png_jmpbuf(png))){

		MESSAGE("ERROR");
		return -1;
	}

	png_init_io(png, png_file);
	png_read_info(png, info);

	img->width = png_get_image_width(png, info);
	img->height = png_get_image_height(png, info);

	png_byte color_type = png_get_color_type(png, info);
	png_byte bit_depth = png_get_bit_depth(png, info);

	if(bit_depth == 16)
		png_set_strip_16(png);

	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	if(color_type == PNG_COLOR_TYPE_RGB ||
	     color_type == PNG_COLOR_TYPE_GRAY ||
	     color_type == PNG_COLOR_TYPE_PALETTE)
	    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if(color_type == PNG_COLOR_TYPE_GRAY ||
	     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	    png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * img->height);
	for(int y = 0; y < img->height; y++)
		row_pointers[y] = (png_bytep *)malloc(png_get_rowbytes(png, info));

	png_read_image(png, row_pointers);

	img->pixels = (struct pixel *)malloc((img->width * img->height) * sizeof(struct pixel));
	if(!img->pixels){

		perror("error");
		return -1;
	}

	memset(img->pixels, 0, (img->width * img->height) * sizeof(struct pixel));

	/*for(int i = 0; i < img->width * img->height; i++){

		img->pixels[i].pix = (struct rgb_pixel *)malloc(sizeof(struct rgb_pixel));
		if(!img->pixels[i].pix){

			perror("error");
			return -1;
		}
	}*/

	fclose(png_file);
	png_destroy_read_struct(&png, &info, NULL);

	/* processing PNG file data */

	unsigned long int pixel_nr = 0;

	for(int y = 0; y < img->height; y++){

		png_bytep row = row_pointers[y];

		for(int x = 0; x < img->width; x++){

			png_bytep px = &(row[x * 4]);

			img->pixels[pixel_nr].pix.red = px[0];
			img->pixels[pixel_nr].pix.green = px[1];
			img->pixels[pixel_nr].pix.blue = px[2];
			img->pixels[pixel_nr].x = x;
			img->pixels[pixel_nr].y = img->height - y;

			//set_pixel_(px[0], px[1], px[2], x, y);
			//printf("pixel_nr: %ld\n", pixel_nr);
			pixel_nr++;

		}

	}


	return 0;
}
