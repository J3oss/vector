#include "vec/vec.h"

#include <stdlib.h>

#define INIT_CAPACITY 10
#define GROWTH_RATE 3 / 2

//returns pointer to meta data
void *vec_alloc(void *p_vec, size_t dataSize)
{
	size_t total_size = sizeof(meta_t) + dataSize;
	return realloc(p_vec, total_size);
}

void *_impl_vec_new(size_t type_size, size_t capacity)
{
	size_t init_cap = capacity ? capacity : INIT_CAPACITY;

	meta_t *v = vec_alloc(NULL, init_cap * type_size);
	v->size = 0;
	v->tsize = type_size;
	v->capacity = init_cap;

	return ++v;
}

void *_impl_vec_shrink_fit(void *vec)
{
	meta_t *new_v = vec_alloc(_VEC_META_PTR(vec), vec_size(vec) * vec_type_size(vec));
	new_v->capacity = new_v->size;

	return ++new_v;
}

void *vec_reserve(void *vec, size_t new_capacity)
{
	if (vec_capacity(vec) >= new_capacity)
	{
		return vec;
	}

	meta_t *new_vec = vec_alloc(_VEC_META_PTR(vec), new_capacity * vec_type_size(vec));
	new_vec->capacity = new_capacity;
	return ++new_vec;
}

void *_impl_vec_resize(void *vec, size_t size)
{
	if (size > vec_size(vec))
	{
		vec = vec_reserve(vec, size);
	}

	_VEC_META_PTR(vec)->size = size;

	return vec;
}

void *_impl_vec_grow(void *vec, size_t n)
{
	size_t size = vec_size(vec);
	size_t tsize = vec_type_size(vec);
	size_t capacity = vec_capacity(vec);

	size_t required_size = size + n;
	size_t growth_size = size * GROWTH_RATE;
	if (capacity < required_size)
	{
		size_t new_size = required_size > growth_size ? required_size:growth_size;
		return vec_reserve(vec, new_size);
	}

	return vec;
}

void _impl_vec_remove_ordered(void *vec, size_t index)
{
	size_t tsize = vec_type_size(vec);

	char *dst = (char *)vec + (index * tsize);
	char *src = dst + tsize;
	size_t size = (vec_size(vec) - index - 1) * tsize;

	memmove(dst, src, size);

	_VEC_META_PTR(vec)->size--;
}

void _impl_vec_prep_push_indexed(void *vec, size_t index)
{
	size_t tsize = vec_type_size(vec);

	char *src = (char *)vec + (index * tsize);
	char *dst = src + tsize;
	size_t size = (vec_size(vec) - index) * tsize;

	memmove(dst, src, size);

	_VEC_META_PTR(vec)->size++;
}