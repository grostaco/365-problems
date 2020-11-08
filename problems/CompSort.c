/*
    Problem 3
    Given a list of numbers, arrange them such that the greatest possible combination can be achieved. 
    
    Examples 
    [input] : output
    [9]: 9
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]: 9876543210
    [441, 42]: 44142
    [441, 4, 42, 4444]: 4444444142
    [6, 12, 5]: 6512
    [6, 61, 68]: 68661
    [6, 61, 65]: 66561
*/

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define swap(a,b) ({       \
    __typeof__(a) tmp = a; \
    a = b;                 \
    b = tmp;               \
})

#define min(a,b) (a<b?a:b)

#define ilog2(n) (64 - __builtin_clzl((uint64_t)n))
static uint64_t ipow10[] = {1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10};

static int16_t ilog10(uint64_t x) {
    if (x == 0) {
        // this is obviously not true, but it is required to make cmp_func work. 
        return 1;
    }
    static int16_t log10_estimates[] = { 0, 0,
                                         1, 1, 1,    
                                         2, 2, 2,       
                                         3, 3, 3,       
                                         4, 4, 4, 4,
                                         5, 5, 5,
                                         6, 6, 6,
                                         7, 7, 7, 7,
                                         8, 8, 8,
                                         9, 9, 9,
                                         10, 10 };

    int estimated_log10 = log10_estimates[ilog2(x)];
    return estimated_log10 + (x >= ipow10[estimated_log10]);
}

static uint64_t quick_ten_pow_div(uint64_t x, int n) {
    switch (n) {
        case 0 :
            return x / 1;
        case 1 :
            return x / 10;
        case 2 :
            return x / 100;
        case 3 :
            return x / 1000;
        case 4 :
            return x / 10000;
        case 5 :
            return x / 100000;
        case 6 :
            return x / 1000000;
        case 7 :
            return x / 10000000;
        default :
            __builtin_unreachable();
    } 
}

static uint64_t quick_ten_pow_mod(uint64_t x, int n) {
    switch (n) {
        case 0 :
            return x % 1;
        case 1 :
            return x % 10;
        case 2 :
            return x % 100;
        case 3 :
            return x % 1000;
        case 4 :
            return x % 10000;
        case 5 :
            return x % 100000;
        case 6 :
            return x % 1000000;
        case 7 :
            return x % 10000000;
        default :
            __builtin_unreachable();
    } 
}

int cmp_func(const uint64_t* _x, const uint64_t* _y) {
    uint64_t x = *_x;
    uint64_t y = *_y;
    uint16_t log10_x = ilog10(x);
    uint16_t log10_y = ilog10(y);

    if (log10_x == log10_y) {
        return x-y;
    }
    
    if ((quick_ten_pow_div(x, log10_x - 1) == quick_ten_pow_div(y, log10_y - 1)) && (log10_x == 1 || log10_y == 1)) {
        return quick_ten_pow_mod(x, min(log10_x, log10_y)) - quick_ten_pow_mod(y, min(log10_x, log10_y));
    }

    if (log10_x >= log10_y) {
        return quick_ten_pow_div(x, log10_x - min(log10_x, log10_y)) - quick_ten_pow_div(y, min(log10_x, log10_y)-log10_y);
    }
    return quick_ten_pow_div(x, min(log10_y, log10_x)-log10_x) - quick_ten_pow_div(y, log10_y - min(log10_y, log10_x));
}

#define ARRAY_SIZE(x) (sizeof x / sizeof *x)

int main () {
    uint64_t array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    
    qsort(array, ARRAY_SIZE(array), sizeof *array, (__compar_fn_t)cmp_func);
    for (int i = ARRAY_SIZE(array) - 1 ; i >= 0 ; --i) {
        printf("%d ", array[i]);
    }

}
