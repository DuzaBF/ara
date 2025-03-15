#include "foo.h"

#include "rivec/vector_defines.h"

void foo(const my_array_t *a, const my_array_t *b, my_array_t *c)
{
    for (int i = 0; i < MY_ARRAY_SIZE; i++)
    {
        c->data[i] = a->data[i] + b->data[i];
    }
}

void foo_intr(const my_array_t *a, const my_array_t *b, my_array_t *c)
{
    size_t vl = vsetvl_e32m1(6);

    const int32_t* a_ = a->data;
    const int32_t* b_ = b->data;
    int32_t* c_ = c->data;

    vint32m1_t buf_a = vle32_v_i32m1(a_, vl);
    vint32m1_t buf_b = vle32_v_i32m1(b_, vl);

    vint32m1_t buf_c = vadd(buf_a, buf_b, vl);

    vse32_v_i32m1(c_, buf_c, vl);
}

void bar(const my_array_t *a, my_array_t *b) {
    size_t vl = vsetvl_e32m1(21);
    const int32_t* a_ = a->data;
    int32_t* b_ = b->data;
    vint32m1_t buf_a = vle32_v_i32m1(a_, vl);
    vint32m1_t buf_b = vadd(buf_a, 1, vl);
    vint32m1_t buf_c = vmul(buf_b, 2, vl);
    vse32_v_i32m1(b_, buf_c, vl);
}

void test_vsetvl() {
    size_t vl = vsetvl_e8m1(7);
    volatile int8_t a[7] = {0};
    volatile int8_t b[7] = {0};
    vint8m1_t buf_a = vle8_v_i8m1(a, vl);
    vint8m1_t buf_b = vadd(buf_a, 1, vl);
    vse8_v_i8m1(b, buf_b, vl);
    vl = vsetvl_e32m2(33);
}