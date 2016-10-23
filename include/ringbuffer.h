/******************************************************************************
 * ringbuffer.h

 * Copyright (C) 2016 Dung-Ru Tsai <tsaidungru.ncku@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/kern_return.h>
#endif

#ifdef __cplusplus
extern "C" { /* for inclusion from C++ */
#endif

#define FILE_NAME                       "heap.log"
#define PROPRIETARY_LOGGING 			0
#define NUM_OF_CELL                     (0x10000) //must power of 2
#define RB_CELL_IDX(idx)      			((idx) & (NUM_OF_CELL - 1)) //mod NUM_OF_CELL
#define BILLION 						1000000000L
#define INLINE                        	__attribute__((always_inline))

extern bool reader_end_flag;
struct ringbuff_cell {
        uint32_t curr_heap_size;
        double timestamp;
#if PROPRIETARY_LOGGING
        double curr_frag_size;
        double alloc_time;
        double time_interval;
#endif /* PROPRIETARY_LOGGING */
};

struct ringbuffer
{
        volatile uint32_t writer_idx;
        volatile uint32_t reader_idx;
        volatile uint32_t cell_nums;
        struct ringbuff_cell cell[NUM_OF_CELL]; 
};

void rb_init(struct ringbuffer *rb);
void rb_deinit(struct ringbuffer *rb);
void rb_put(struct ringbuffer *rb, void *value);
void rb_get(struct ringbuffer *rb, void *value);

void clock_get_hw_time(struct timespec *ts);
INLINE double get_curr_time(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* __RINGBUFFER_H__ */
