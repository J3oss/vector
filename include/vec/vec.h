#pragma once

#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	size_t size;
	size_t tsize;
	size_t capacity;
} meta_t;

#define _VEC_META_PTR(X) (((meta_t *)(X)) - 1)
#define _VEC_DATA_PTR(X) (((meta_t *)(X)) + 1)

#define vec(T) T *

#define vec_new(type) \
	(assert(sizeof(type) && "Type size is zero"), \
	_impl_vec_new(sizeof(type), 0))

#define vec_new_cap(type, capacity) \
	(assert(sizeof(type) && "Type size is zero"), \
	_impl_vec_new(sizeof(type), capacity))

#define vec_free(vec) \
	(free(_VEC_META_PTR(vec)))

#define vec_size(vec) \
	(assert(vec && "NULL vec"), \
	_VEC_META_PTR((vec))->size)

#define vec_is_empty(vec) \
	(assert(vec && "NULL vec"), \
	_VEC_META_PTR((vec))->size ? 0:1)

#define vec_capacity(vec) \
	(assert(vec && "NULL vec"), \
	_VEC_META_PTR((vec))->capacity)

#define vec_type_size(vec) \
	(assert(vec && "NULL vec"), \
	_VEC_META_PTR((vec))->tsize)

#define vec_shrink_fit(vec) \
	(assert(vec && "NULL vec"), \
	vec = _impl_vec_shrink_fit(vec))

#define vec_resize(vec, size) \
	(assert(vec && "NULL vec"), \
	vec = _impl_vec_resize(vec, size))

#define vec_pop(vec) \
	(assert(vec && "NULL vec"), assert(vec_size(vec) && "pop on empty vector"), \
	vec[--_VEC_META_PTR((vec))->size])

#define vec_push(vec, data) \
	(assert(vec && "NULL vec"), \
	vec = _impl_vec_grow(vec, 1), vec[_VEC_META_PTR((vec))->size++] = data)

#define vec_remove(vec, index) \
	(assert(vec && "NULL vec"), assert(index >= 0 && index < vec_size(vec) && "index out of bounds"), \
	vec[index] = vec[--_VEC_META_PTR((vec))->size])

#define vec_remove_ordered(vec, index) \
	(assert(vec && "NULL vec"), assert(index >= 0 && index < vec_size(vec) && "index out of bounds"), \
	_impl_vec_remove_orderer(vec, index))

#define vec_push_indexed(vec, index, data) \
	(assert(vec && "NULL vec"), assert(index >= 0 && index <= vec_size(vec) && "index out of bounds"), \
	vec = _impl_vec_grow(vec, 1), \
	_impl_vec_prep_push_indexed(vec, index), vec[index] = data)

void *_impl_vec_shrink_fit(void *vec);
void *_impl_vec_grow(void *vec, size_t n);
void *_impl_vec_resize(void *vec, size_t size);
void *_impl_vec_new(size_t type_size, size_t capacity);
void _impl_vec_remove_ordered(void *vec, size_t index);
void _impl_vec_prep_push_indexed(void *vec, size_t index);