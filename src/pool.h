/*
 * pool.h
 *
 *  Created on: Jan 16, 2016
 *      Author: os
 */

#ifndef POOL_H_
#define POOL_H_

struct pool_element{

	void *ptr;

	struct pool_element *next;
};

struct pool{

	struct pool_element *elements;
	unsigned long int elements_count;

};

#define		free_pool(pool) 	__free_pool(pool); \
								pool = NULL;

struct pool *create_pool();
int add_to_pool(struct pool *pool, void *ptr);
void __free_pool(struct pool *pool);



#endif /* POOL_H_ */
