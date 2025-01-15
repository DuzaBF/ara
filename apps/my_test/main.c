#include <stdint.h>
#include <string.h>

#include "util.h"
#include <stdio.h>

#include "foo.h"

int main()
{
    my_array_t a, b, c;
    for (int i = 0; i < 5; ++i) {
        a.data[i] = i;
        b.data[i] = i;
    }
    foo(&a, &b, &c);
    for (int i = 0; i < 5; ++i) {
        printf("c[%d] = %d\n", i, c.data[i]);
    }
}
