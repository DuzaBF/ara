#include <stdint.h>
#include <string.h>

#ifdef SPIKE
#include "util.h"
#include <stdio.h>
#elif defined ARA_LINUX
#include <stdio.h>
#else
#include "printf.h"
#endif

#include "foo.h"

int main()
{
    my_array_t a, b, c;
    for (int i = 0; i < 5; ++i) {
        a.data[i] = i;
    }
    bar(&a, &b);
    foo_intr(&a, &b, &c);
    for (int i = 0; i < 5; ++i) {
        printf("a[%d] = %d; ", i, a.data[i]);
        printf("b[%d] = %d; ", i, b.data[i]);
        printf("c[%d] = %d\n", i, c.data[i]);
    }
}
