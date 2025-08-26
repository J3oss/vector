#include "vec/vec.h"

#include <stdio.h>
#include <assert.h>

int main()
{
    // int test
	{
		vec(int) v = vec_new(int);
		assert(v != NULL);

		for (int i = 0; i < 5; i++) {
			vec_push(v, i);
		}
		assert(vec_size(v) == 5);

		// pop
		int last = vec_pop(v);
		assert(last == 4);
		assert(vec_size(v) == 4);

		// remove (fast)
		int old2 = v[3];
		vec_remove(v, 1);
		assert(vec_size(v) == 3);
		assert(v[1] == old2);

		// resize up
		vec_resize(v, 10);
		assert(vec_size(v) == 10);

		// resize down
		vec_resize(v, 2);
		assert(vec_size(v) == 2);

		// push more to trigger growth
		size_t cap_before = vec_capacity(v);
		for (int i = 0; i < 50; i++) {
			vec_push(v, i);
		}
		assert(vec_size(v) == 52);
		assert(vec_capacity(v) >= 52);
		assert(vec_capacity(v) > cap_before);

		// shrink
		vec_shrink_fit(v);
		assert(vec_size(v) == vec_capacity(v));

		// empty test
		while (vec_size(v)) {
			vec_pop(v);
		}
		assert(vec_is_empty(v));

		vec_free(v);
	}
    
	// user-defined type test
    {
		struct struct03
		{
			char a;
			char b;
			char c;
		};

		struct struct03 s03_0 = {33, 3, 0};
		struct struct03 s03_1 = {34, 4, 1};
		struct struct03 s03_2 = {35, 5, 2};

		vec(struct struct03) v_s03 = vec_new(struct struct03);
		assert(v_s03 != NULL);

		// push
		vec_push(v_s03, s03_0);
		vec_push(v_s03, s03_1);
		vec_push(v_s03, s03_2);
		assert(vec_size(v_s03) == 3);

		// verify contents
		for (size_t i = 0; i < vec_size(v_s03); ++i) {
			assert(v_s03[i].a == (char)(33 + i));
			assert(v_s03[i].b == (char)(3 + i));
			assert(v_s03[i].c == (char)(0 + i));
		}

		// pop
		struct struct03 popped = vec_pop(v_s03);
		assert(popped.a == 35 && popped.b == 5 && popped.c == 2);
		assert(vec_size(v_s03) == 2);

		// remove (swap with last)
		struct struct03 last = v_s03[1];
		vec_remove(v_s03, 0);
		assert(vec_size(v_s03) == 1);
		assert(v_s03[0].a == last.a &&
			v_s03[0].b == last.b &&
			v_s03[0].c == last.c);

		// resize up
		vec_resize(v_s03, 5);
		assert(vec_size(v_s03) == 5);

		// resize down
		vec_resize(v_s03, 2);
		assert(vec_size(v_s03) == 2);

		// growth test
		size_t cap_before = vec_capacity(v_s03);
		for (int i = 0; i < 20; i++) {
			struct struct03 tmp = { (char)(40 + i),
									(char)(10 + i),
									(char)(i) };
			vec_push(v_s03, tmp);
		}
		assert(vec_size(v_s03) == 22);
		assert(vec_capacity(v_s03) >= 22);
		assert(vec_capacity(v_s03) > cap_before);

		// shrink fit
		vec_shrink_fit(v_s03);
		assert(vec_size(v_s03) == vec_capacity(v_s03));

		vec_free(v_s03);
	}

	printf("vector tests passed!\n");
}
