#include "foo.h"

void foo(const my_array_t *a,  const my_array_t *b, my_array_t *c)
{
    for (int i = 0; i < MY_ARRAY_SIZE; i++)
    {
        c->data[i] = a->data[i] + b->data[i];
    }
}