#include "vec.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#define INIT_CAPACITY 10
#define GROWTH_RATE 3 / 2

typedef struct
{
	size_t size;
	size_t tsize;
	size_t capacity;
} meta_data_t;

#define DATA_PTR(X) ((((meta_data_t *)(X))) + 1)
#define METADATA_PTR(X) (((meta_data_t *)(X)) - 1)

#define SIZE(X) METADATA_PTR((*(X)))->size
#define TSIZE(X) METADATA_PTR((*(X)))->tsize
#define CAPACITY(X) METADATA_PTR((*(X)))->capacity

//returns pointer to meta data
void *vec_alloc(void *pMetaData, size_t dataSize)
{
	void *p_vec = pMetaData ? pMetaData : NULL;
	size_t total_size = sizeof(meta_data_t) + dataSize;

	return realloc(p_vec, total_size);
}

//returns pointer to data
void *_impl_new_vec(size_t type_size, size_t capacity)
{
	size_t init_cap = capacity ? capacity : INIT_CAPACITY;

	meta_data_t *v = vec_alloc(NULL, init_cap * type_size);
	v->size = 0;
	v->tsize = type_size;
	v->capacity = init_cap;

	return ++v;
}

void vec_free(void *p_vec)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	free(METADATA_PTR(*pp_vec));
}

size_t vec_size(void *p_vec)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	return SIZE(pp_vec);
}

size_t vec_capacity(void *p_vec)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	return CAPACITY(pp_vec);
}

size_t vec_element_size(void *p_vec)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	return TSIZE(pp_vec);
}

bool vec_is_empty(void *p_vec)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	return SIZE(pp_vec) ? false : true;
}

void vec_reserve(void **pp_vec, size_t new_capacity)
{
	assert(*pp_vec);

	if (CAPACITY(pp_vec) > new_capacity)
	{
		return;
	}

	meta_data_t *new_vec = vec_alloc(METADATA_PTR(*pp_vec), new_capacity * TSIZE(pp_vec));
	new_vec->capacity = new_capacity;
	*pp_vec = ++new_vec;
}

void vec_resize(void *p_vec, size_t size)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	if (size > SIZE(pp_vec))
	{
		vec_reserve(pp_vec, size);
	}

	METADATA_PTR(*pp_vec)->size = size;
}

void vec_shrink_fit(void *p_vec)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	meta_data_t *new_v = vec_alloc(METADATA_PTR(*pp_vec), SIZE(pp_vec) * CAPACITY(pp_vec));
	new_v->size = new_v->size;
	new_v->capacity = new_v->size;

	*pp_vec = ++new_v;
}

size_t vec_push(void *p_vec, void *data)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	size_t size = SIZE(pp_vec);
	size_t tsize = TSIZE(pp_vec);
	assert(size >= 0);
	assert(tsize > 0);

	if (CAPACITY(pp_vec) < size + 1)
	{
		vec_reserve(pp_vec, size * GROWTH_RATE);
	}

	char *dest = (char *)*pp_vec + size * tsize;
	memcpy(dest, data, tsize);

	METADATA_PTR(*pp_vec)->size = size + 1;

	return size;
}

void vec_remove(void *p_vec, size_t index)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	size_t size = SIZE(pp_vec);
	size_t tsize = TSIZE(pp_vec);
	assert(size >= 0);
	assert(tsize > 0);

	if (size <= 0)
	{
		return;
	}

	METADATA_PTR(*pp_vec)->size = --size;

	char *dest = (char *)*pp_vec + index * tsize;
	char *src = (char *)*pp_vec + size * tsize;
	memcpy(dest, src, tsize);
}

void vec_remove_ordered(void *p_vec, size_t index)
{
	void **pp_vec = p_vec;
	assert(*pp_vec);

	size_t size = SIZE(pp_vec);
	size_t tsize = TSIZE(pp_vec);
	assert(size >= 0);
	assert(tsize > 0);

	if (size <= 0)
	{
		return;
	}

	METADATA_PTR(*pp_vec)->size = --size;

	char *dest = (char *)*pp_vec + index * tsize;
	char *src = dest + tsize;
	memcpy(dest, src, (size - index) * tsize);
}