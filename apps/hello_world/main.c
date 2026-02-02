// Copyright 2020 ETH Zurich and University of Bologna.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Author: Matheus Cavalcante, ETH Zurich

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

#include <riscv_vector.h>

#define LENGTH 61

static int32_t a[LENGTH] = {};

static inline int start_inst_count() {
    // requires Zicntr extensions
    int counter;
    asm volatile("rdinstret %0" : "=r"(counter));
    return counter;
}
static inline int end_inst_count(int start) {
    // requires Zicntr extensions
    int counter;
    asm volatile("rdinstret %0" : "=r"(counter));
    int count = counter - start;
    return count;
}

void unit_stride(int32_t* cur_pos, size_t len) {
    for (size_t vl = 0; len > 0; len -= vl) {
        vl = __riscv_vsetvl_e32m1(len);
        // printf("vl %d\n", vl);
        vint32m1_t a_vec = __riscv_vle32_v_i32m1(cur_pos, vl);
        vint32m1_t b_vec = __riscv_vadd_vx_i32m1(a_vec, 100, vl);
        __riscv_vse32_v_i32m1(cur_pos, b_vec, vl);
        cur_pos = cur_pos + vl;
    }
}

void strided(int32_t* cur_pos, size_t len) {
    // stride is byte sized
    size_t vl = __riscv_vsetvl_e32m1(4);
    vint32m1_t a_vec = __riscv_vlse32_v_i32m1(cur_pos, 3 * sizeof(int32_t), vl);
    vint32m1_t b_vec = __riscv_vadd_vx_i32m1(a_vec, 2000, vl);
    __riscv_vsse32_v_i32m1(cur_pos, 3 * sizeof(int32_t), b_vec, vl);
}

void indexed(int32_t* cur_pos, size_t len) {
    // index is of byte
    uint8_t offsets[] = {3 * sizeof(int32_t), 5 * sizeof(int32_t), 7 * sizeof(int32_t)};
    size_t vl = __riscv_vsetvl_e8mf4(3);
    vuint8mf4_t off_vec = __riscv_vle8_v_u8mf4(offsets, vl);
    vl = __riscv_vsetvl_e32m1(3);
    printf("vloxei\n");
    vint32m1_t a_vec = __riscv_vloxei8_v_i32m1(cur_pos, off_vec, vl);
    vint32m1_t b_vec = __riscv_vadd_vx_i32m1(a_vec, 30000, vl);
    __riscv_vsoxei8_v_i32m1(cur_pos, off_vec, b_vec, vl);
}

void chaining(int32_t* cur_pos, size_t len) {
    for (size_t vl = 0; len > 0; len -= vl) {
        vl = __riscv_vsetvl_e32m1(len);
        vint32m1_t a_vec = __riscv_vmv_s_x_i32m1(100, vl);
        vint32m1_t b_vec = __riscv_vadd_vx_i32m1(a_vec, 20, vl);
        vint32m1_t c_vec = __riscv_vmul_vx_i32m1(b_vec, 3, vl);
        __riscv_vse32_v_i32m1(cur_pos, c_vec, vl);
        cur_pos = cur_pos + vl;
    }
}

int main() {
    // printf("Before\n");
    // for (int i = 0; i < LENGTH; ++i) {
    //     a[i] = i;
    //     printf("a[%02i] = %d\n", i, a[i]);
    // }
    // int start = start_inst_count();
    chaining(a, LENGTH);
    // int count = end_inst_count(start);
    // printf("Used %d instructions\n", count);

    // strided(a, LENGTH);

    // indexed(a, LENGTH);

    // printf("After\n");
    // for (int i = 0; i < LENGTH; ++i) {
    //     printf("a[%02i] = %d\n", i, a[i]);
    // }
}
