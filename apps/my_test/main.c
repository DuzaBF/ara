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
    my_array_t a, b;
    for (int i = 0; i < MY_ARRAY_SIZE; ++i)
    {
        a.data[i] = (((uint32_t)i) << 24) | (((uint32_t)i) << 16) | (((uint32_t)i) << 8) | (((uint32_t)i) << 0);
    }
    bar(&a, &b);
    // test_vsetvl();
    // foo_intr(&a, &b, &c);
    for (int i = 10; i < 11; ++i) {
        printf("a[%d] = %#010X; ", i, a.data[i]);
        printf("b[%d] = %#010X; ", i, b.data[i]);
    }
    printf("\n");
}
