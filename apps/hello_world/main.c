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

#define LENGTH 13

static uint64_t a[LENGTH] = {};

int chaining(uint64_t* cur_pos, size_t len) {
    for (size_t vl = 0; len > 0; len -= vl) {
        vl = __riscv_vsetvl_e64m1(len);
        vuint64m1_t a_vec = __riscv_vmv_v_x_u64m1(0, vl);
        vbool64_t m_vec = __riscv_vmseq_vx_u64m1_b64(a_vec, 0, vl);
        vuint64m1_t b_vec = __riscv_viota_m_u64m1(m_vec, vl);
        vuint64m1_t c_vec = __riscv_vadd_vx_u64m1(b_vec, 100, vl);
        vuint64m1_t d_vec = __riscv_vmul_vx_u64m1(c_vec, 2, vl);
        __riscv_vse64_v_u64m1(cur_pos, d_vec, vl);
        cur_pos = cur_pos + vl;
    }
    return 0;
}

int chaining_asm(uint64_t* cur_pos, size_t len) {
    int a = 100;
    int b = 2;
    for (size_t vl = 0; len > 0; len -= vl) {
        asm volatile("vsetvli %0, %1, e64, m1, ta, ma" : "=r"(vl) : "r"(len));
        asm volatile("vmv.v.i v8, 0");
        asm volatile("vmseq.vi v8, v8, 0");
        asm volatile("viota.m v9, v8");
        asm volatile("vadd.vx v10, v9, %0" :: "r"(a));
        asm volatile("vmul.vx v11, v10, %0" :: "r"(b));
        asm volatile("vse64.v v11, (%0)" :: "r"(cur_pos));
        cur_pos = cur_pos + vl;
    }
    return 0;
}

int main() {
    // chaining(a, LENGTH);
    chaining_asm(a, LENGTH);
}
