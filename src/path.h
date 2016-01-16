/*
 * path.h
 *
 *  Created on: Jan 15, 2016
 *      Author: os
 */

#ifndef PATH_H_
#define PATH_H_

#include "pixmap.h"

struct edge_pixel{

	unsigned int x;
	unsigned int y;

	struct edge_pixel *next;
};

struct edge{

	struct edge_pixel *edge_pixels;

	unsigned int length;

};


struct edge *make_path(struct b8_image *bin_image, unsigned char object_color);


#endif /* PATH_H_ */
