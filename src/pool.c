#include "pool.h"
#include <stdlib.h>

struct pool *create_pool(){

	struct pool* pool = (struct pool *)malloc(sizeof(struct pool));
	if(!pool)
		return NULL;

	pool->elements = NULL;
	pool->elements_count = 0;

	return pool;

}

int add_to_pool(struct pool *pool, void *ptr){

	if(!ptr || !pool)
		return -1;

	if(!pool->elements_count){

		pool->elements = (struct pool_element *)malloc(sizeof(struct pool_element));
		if(!pool->elements)
			return -1;
	}

}

void free_pool(struct pool *pool){


}
