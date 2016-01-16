/*
 * image.h
 *
 *  Created on: Jan 7, 2016
 *      Author: os
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "pixmap.h"


int read_image(const char *file_path, struct image *img);


struct b8_image *binarize_image(struct image *image);



#endif /* IMAGE_H_ */
