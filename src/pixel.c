/*
 * pixel.c
 *
 *  Created on: Jan 7, 2016
 *      Author: os
 */

#include "pixmap.h"
#include "main.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static struct pixel *bufer = NULL;
static unsigned int buf_width;
static unsigned int buf_height;


int write_pix_in_buf(struct pixel *pix){

	if(!pix || pix->x > buf_width || pix->y > buf_height || !bufer)
		return -1;

	struct pixel *p = &bufer[(pix->x * buf_height + pix->y + pix->x)];
	memcpy((void *)p , pix, sizeof(struct pixel));

	return 0;
}

struct pixel *read_pix_from_buf(long x, long y){

	return &bufer[(x * buf_height + y + x)];
}

void flush_bufer(){

	if(!bufer)
		return;

	glBegin(GL_POINTS);

	for(long i = 0; i < buf_width * buf_height; i++){

		glColor3f(bufer[i].pix.red / 255.0, bufer[i].pix.green / 255.0, bufer[i].pix.blue / 255.0);
		glVertex2i(bufer[i].x, bufer[i].y);

	}

	glEnd();
	glFlush();
}

int bufer_init(long width, long height){

	bufer = (struct pixel *)malloc(((width + 1) * (height + 1)) * sizeof(struct pixel));
	if(!bufer){

		perror("error");
		return -1;
	}

	buf_height = height;
	buf_width = width;
	printf("buf_sz: %ld\n", (width + 1) * (height + 1));

	/*
	long pix_nr = 0;



	for(unsigned int x = 0; x <= width; x++){

		for(unsigned int y = 0; y <= height; y++){

			bufer[pix_nr].x = x;
			bufer[pix_nr].y = y;

			pix_nr++;
		}
	}*/

	return 0;
}


int set_pixel(struct pixel *pix){

	if(!pix){

		MESSAGE("pix == NULl!");
		return -1;

	}

	glColor3f(pix->pix.red / 255.0, pix->pix.green / 255.0, pix->pix.blue / 255.0);
	glBegin(GL_POINTS);
	glVertex2i(pix->x, pix->y);
	glEnd();
	glFlush();

	write_pix_in_buf(pix);


	return 0;

}

int set_pixels(struct pixel *pix, long count){

	glBegin(GL_POINTS);

	for(long i = 0; i < count; i++){

		glColor3f(pix[i].pix.red / 255.0, pix[i].pix.green / 255.0, pix[i].pix.blue / 255.0);
		glVertex2i(pix[i].x, pix[i].y);

		write_pix_in_buf(&pix[i]);
	}

	glEnd();
	glFlush();

	return 0;
}

void set_pixel_(register unsigned char red, register unsigned char green,
				register unsigned char blue,
			    register unsigned int x, register unsigned int y){



	struct pixel pix;

	pix.pix.blue = blue;
	pix.pix.red = red;
	pix.pix.green = green;
	pix.x = x;
	pix.y = y;

	//set_pixel(&pix);

	glColor3f(red / 255.0, green / 255.0, blue / 255.0);
	glVertex2i(x, y);
	write_pix_in_buf(&pix);

}


