#pragma once
#include "stdint.h"

#define MY_ARRAY_SIZE (128)

typedef struct  {
    uint32_t data[MY_ARRAY_SIZE];
} my_array_t;

void foo(const my_array_t *a,  const my_array_t *b, my_array_t *c);