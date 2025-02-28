#include "../vec.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

struct struct03
{
	char a;
	char b;
	char c;
};

struct struct07
{
	uint32_t a;
	uint16_t b;
	char c;
};

struct struct11
{
	uint64_t a;
	uint16_t b;
	char c;
};

struct struct17
{
	uint64_t a;
	uint64_t b;
	char c;
};

int main()
{
	//int vector test
	vec(int) v = new_vec(int, 0);
	assert(v != 0);

	printf("Initial size: %llu\n", vec_size(&v));
	printf("Initial capacity: %llu\n", vec_capacity(&v));

	for (uint32_t i = 0; i < 10; ++i)
	{
		vec_push(&v, &i);
	}

	printf("Size after pushing elements: %llu\n", vec_size(&v));
	assert(vec_size(&v) == 10);
	printf("Capacity after pushing elements: %llu\n", vec_capacity(&v));

	for (uint32_t i = 0; i < vec_size(&v); ++i)
	{
		printf("Element at index %d: %d\n", i, v[i]);
		assert(v[i] == i);
	}

	vec_resize(&v, 15);

	printf("Size after resizing: %llu\n", vec_size(&v));
	assert(vec_size(&v) == 15);
	printf("Capacity after resizing: %llu\n", vec_capacity(&v));

	for (int i = 10; i < 15; ++i)
	{
		vec_push(&v, &i);
	}

	printf("Size after pushing more elements: %llu\n", vec_size(&v));
	assert(vec_size(&v) == 20);
	printf("Capacity after pushing more elements: %llu\n", vec_capacity(&v));
	assert(vec_capacity(&v) == 22); //15 * 3/2

	vec_shrink_fit(&v);
	printf("Size after shrink fit: %llu\n", vec_size(&v));
	printf("Capacity after shrink fit: %llu\n", vec_capacity(&v));
	assert(vec_size(&v) == vec_capacity(&v) && vec_size(&v) == 20);

	if (vec_is_empty(&v))
	{
		printf("The vector is empty.\n");
	}
	else
	{
		printf("The vector is not empty.\n");
	}
	assert(!vec_is_empty(&v));

	vec_free(&v);

	//user defined test
	struct struct03 s03_0 = {33, 3, 0};
	struct struct07 s07_0 = {777, 77, 7};
	struct struct11 s11_0 = {111111, 1111, 11};
	struct struct17 s17_0 = {171717, 1717, 17};
	struct struct03 s03_1 = {34, 4, 1};
	struct struct07 s07_1 = {778, 78, 8};
	struct struct11 s11_1 = {111112, 1112, 12};
	struct struct17 s17_1 = {171718, 1718, 18};
	struct struct03 s03_2 = {35, 5, 2};
	struct struct07 s07_2 = {779, 79, 9};
	struct struct11 s11_2 = {111113, 1113, 13};
	struct struct17 s17_2 = {171719, 1719, 19};

	vec(struct struct03) v_s03 = new_vec(struct struct03, 0);
	vec(struct struct07) v_s07 = new_vec(struct struct07, 0);
	vec(struct struct11) v_s11 = new_vec(struct struct11, 0);
	vec(struct struct17) v_s17 = new_vec(struct struct17, 0);

	vec_push(&v_s03, &s03_0);
	vec_push(&v_s03, &s03_1);
	vec_push(&v_s03, &s03_2);

	vec_push(&v_s07, &s07_0);
	vec_push(&v_s07, &s07_1);
	vec_push(&v_s07, &s07_2);

	vec_push(&v_s11, &s11_0);
	vec_push(&v_s11, &s11_1);
	vec_push(&v_s11, &s11_2);

	vec_push(&v_s17, &s17_0);
	vec_push(&v_s17, &s17_1);
	vec_push(&v_s17, &s17_2);

	for (uint32_t i = 0; i < vec_size(&v_s03); ++i)
	{
		printf("vS03 Element at index %d: { %u, %u, %u }\n", i, v_s03[i].a, v_s03[i].b, v_s03[i].c);
		assert(v_s03[i].a == i + 33 && v_s03[i].b == i + 3 && v_s03[i].c == i + 0);

		printf("vS07 Element at index %d: { %u, %u, %u }\n", i, v_s07[i].a, v_s07[i].b, v_s07[i].c);
		assert(v_s07[i].a == i + 777 && v_s07[i].b == i + 77 && v_s07[i].c == i + 7);

		printf("vS11 Element at index %d: { %llu, %u, %u }\n", i, v_s11[i].a, v_s11[i].b, v_s11[i].c);
		assert(v_s11[i].a == i + 111111 && v_s11[i].b == i + 1111 && v_s11[i].c == i + 11);

		printf("vS17 Element at index %d: { %llu, %llu, %u }\n", i, v_s17[i].a, v_s17[i].b, v_s17[i].c);
		assert(v_s17[i].a == i + 171717 && v_s17[i].b == i + 1717 && v_s17[i].c == i + 17);
	}

	vec_free(&v_s03);
	vec_free(&v_s07);
	vec_free(&v_s11);
	vec_free(&v_s17);
}
