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

		pool->elements->ptr = ptr;
		pool->elements->next = NULL;

		pool->elements_count = 1;

		return 0;

	}

	struct pool_element *element = pool->elements;

	while(element->next)
		element = element->next;

	element->next = (struct pool_element *)malloc(sizeof(struct pool_element));

	element = element->next;
	element->ptr = ptr;
	element->next = NULL;

	pool->elements_count++;

	return 0;


}

void free_pool(struct pool *pool){

	if(!pool)
		return;

	if(!pool->elements){

		free(pool);

		return;
	}

	struct pool_element *element = pool->elements;
	struct pool_element *prev_element;

	while(element){

		free(element->ptr);

		prev_element = element;
		element = prev_element->next;

		free(prev_element);

	}

	free(pool);


}
