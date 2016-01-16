/*
 * binarizer.c
 *
 *  Created on: Jan 8, 2016
 *      Author: os
 */


#include "image.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#define		RED_GRAYSCALE_MUL		0.299 /*0.2126*/
#define		GREEN_GRAYSCALE_MUL		0.587 /*0.7152*/
#define		BLUE_GRAYSCALE_MUL		0.114 /*0.0722*/

struct b8_image *make_grayscale_image(struct image *image);

unsigned char find_max_gray(struct b8_image *gr_image);
unsigned char find_min_gray(struct b8_image *gr_image);

//unsigned char yanni_method(struct b8_image *gr_image);
unsigned char middle_method(struct b8_image *gr_image);
unsigned char otsu_method(struct b8_image *gr_img);

struct b8_image *binarize_image(struct image *image){

	struct b8_image *grayscale_img = make_grayscale_image(image);
	if(!grayscale_img)
		return NULL;

	//unsigned char max_gray = find_max_gray(grayscale_img);
	//unsigned char min_gray = find_min_gray(grayscale_img);

	//unsigned char bin_st = middle_method(grayscale_img);

	unsigned char bin_st = otsu_method(grayscale_img);

	for(unsigned int p = 0; p < grayscale_img->width * grayscale_img->height; p++){

		if(grayscale_img->pixels[p].color >= bin_st){

			grayscale_img->pixels[p].color = 255;

		}else{

			grayscale_img->pixels[p].color = 0;
		}
	}

	return grayscale_img;
}

unsigned char middle_method(struct b8_image *gr_img){

	unsigned char max_gray = find_max_gray(gr_img);
	unsigned char min_gray = find_min_gray(gr_img);

	return ((max_gray + min_gray) / 2);

}


unsigned char find_max_gray(struct b8_image *gr_image){

	if(!gr_image)
		return 0;

	unsigned char max = gr_image->pixels[0].color;

	for(unsigned int p = 0; p < gr_image->width * gr_image->height; p++){

		if(gr_image->pixels[p].color > max)
			max = gr_image->pixels[p].color;

	}

	return max;

}

unsigned char find_min_gray(struct b8_image *gr_image){

	if(!gr_image)
		return 0;

	unsigned char min = gr_image->pixels[0].color;

	for(unsigned int p = 0; p < gr_image->width * gr_image->height; p++){

		if(gr_image->pixels[p].color < min)
			min = gr_image->pixels[p].color;

	}

	return min;

}

unsigned char otsu_method(struct b8_image *gr_img){

	if(!gr_img)
		return 0;

	unsigned char max_gray = find_max_gray(gr_img);
	unsigned char min_gray = find_min_gray(gr_img);

	//printf("%d %d\n", max_gray, min_gray);

	unsigned int hist_sz = max_gray - min_gray + 1;

	int *hist = (int *)malloc(hist_sz * sizeof(int));
	if(!hist)
		return 0;

	for(int i = 0; i < hist_sz; i++)
		hist[i] = 0;

	for(unsigned int i = 0; i < gr_img->width * gr_img->height; i++){

		hist[gr_img->pixels[i].color - min_gray]++;
	}

	int tmp1 = 0;
	int tmp = 0;
	int alpha = 0;
	int beta = 0;

	for(unsigned i = 0; i <= (max_gray - min_gray); i++){

		tmp += i * hist[i];
		tmp1 += hist[i];
	}

	double sigma, max_sigma=-1;
	double w1,a;
	unsigned char threshold;

	for(unsigned int i = 0; i < (max_gray - min_gray); i++){

		alpha += i * hist[i];
		beta += hist[i];

		w1 = (double)beta / tmp1;
		a = (double)alpha / beta - (double)(tmp - alpha) / (tmp1 - beta);

		sigma = w1 * (1 - w1)*a*a;

		if(sigma > max_sigma){

			max_sigma = sigma;
			threshold = i;
		}

	}

	free(hist);

	//printf("%d", threshold);

	return threshold;
}

struct b8_image *make_grayscale_image(struct image *image){

	struct b8_image *gr_image = (struct b8_image *)malloc(sizeof(struct b8_image));
	if(!gr_image)
		return NULL;

	gr_image->pixels = (struct b8_pixel *)malloc(sizeof(struct b8_pixel) * image->width * image->height);
	if(!gr_image->pixels){

		free(gr_image);

		return NULL;
	}

	gr_image->width = image->width;
	gr_image->height = image->height;

	for(unsigned int i = 0; i < image->width * image->height; i++){


		gr_image->pixels[i].color = image->pixels[i].pix.red * RED_GRAYSCALE_MUL +
							image->pixels[i].pix.green * GREEN_GRAYSCALE_MUL +
							image->pixels[i].pix.blue * BLUE_GRAYSCALE_MUL;


		gr_image->pixels[i].x = image->pixels[i].x;
		gr_image->pixels[i].y = image->pixels[i].y;

	}

	return gr_image;

}

