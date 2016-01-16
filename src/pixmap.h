/*
 * pixmap.h
 *
 *  Created on: Jan 7, 2016
 *      Author: os
 */

#ifndef PIXMAP_H_
#define PIXMAP_H_


struct rgb_pixel{

	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct rgb_pixmap{

	struct rgb_pixel *pixel;
	long width;
	long height;

};


struct pixel{

	struct rgb_pixel pix;
	unsigned int x;
	unsigned int y;
};


struct image{

	struct pixel *pixels;
	unsigned long width;
	unsigned long height;

};

struct b8_pixel{

	unsigned char color;
	unsigned int x;
	unsigned int y;
};

struct b8_image{

	struct b8_pixel *pixels;
	unsigned long width;
	unsigned long height;

};


int bufer_init(long width, long height);
void flush_bufer();
struct pixel *read_pix_from_buf(long x, long y);
int write_pix_in_buf(struct pixel *pix);

int set_pixel(struct pixel *pix);
void set_pixel_(register unsigned char red, register unsigned char green,
				register unsigned char blue,
			    register unsigned int x, register unsigned int y);
int set_pixels(struct pixel *pix, long count);


#endif /* PIXMAP_H_ */
