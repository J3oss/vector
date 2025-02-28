#pragma once

#include <stddef.h>
#include <stdbool.h>

#define vec(T) T *

#define new_vec(T, CAP) _impl_new_vec(sizeof(T), CAP)
// NOLINTNEXTLINE
void *_impl_new_vec(size_t element_size, size_t capacity);

void vec_free(void *vec);

size_t vec_size(void *vec);
size_t vec_capacity(void *vec);
size_t vec_element_size(void *vec);

bool vec_is_empty(void *vec);

void vec_resize(void *vec, size_t size);

void vec_shrink_fit(void *vec);

void vec_remove(void *vec, size_t index);
void vec_remove_ordered(void *vec, size_t index);

size_t vec_push(void *vec, void *value);