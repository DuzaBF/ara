#pragma once

#include "my_array.h"

void foo(const my_array_t *a, const my_array_t *b, my_array_t *c);
void foo_intr(const my_array_t *a, const my_array_t *b, my_array_t *c);
void bar(const my_array_t *a, my_array_t *b);
void test_vsetvl();