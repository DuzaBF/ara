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

static my_array_t a __attribute__((section(".my_data_a")));
static my_array_t b __attribute__((section(".my_data_b")));

int main()
{
    printf("&a = %#010X\n", (uint32_t)&a.data);
    printf("&b = %#010X\n", (uint32_t)&b.data);
    for (int i = 0; i < MY_ARRAY_SIZE; ++i)
    {
        a.data[i] = (((uint32_t)i) << 24) | (((uint32_t)i) << 16) | (((uint32_t)i) << 8) | (((uint32_t)i) << 0);
        // a.data[3] = 0x03030303
    }
    bar(&a, &b);
    for (int i = 0; i < 25; ++i)
    {
        printf("a[%d] = %#010X; ", i, a.data[i]);
        printf("b[%d] = %#010X; ", i, b.data[i]);
        printf("\n");
    }
    printf("\n");
}
