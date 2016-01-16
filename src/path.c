#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "pixmap.h"
#include "path.h"


struct edge *make_path(struct b8_image *bin_image, unsigned char object_color){

	if(!bin_image)
		return NULL;

	struct edge *edge = (struct edge *)malloc(sizeof(struct edge));
	if(!edge)
		return NULL;

	for(unsigned int p = 0; p < bin_image->width * bin_image->height; p++){


	}

	return edge;

}
