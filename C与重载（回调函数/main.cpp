//接口归一化

#include <stdio.h>
#include <stdarg.h>

void exchange_int(void *a, void *b)
{
    int*_a = (int *)a;
    int*_b = (int *)b;
    int tmp = 0;

    tmp = *_a;
    *_a = *_b;
    *_b = tmp;
}

void exchange_double(void *a, void *b)
{
    double *_a = (double *)a;
    double *_b = (double *)b;
    double tmp = 0;

    tmp = *_a;
    *_a = *_b;
    *_b = tmp;
}
typedef void (*func)(void* ,void*);
void swap(func exchange, void *a, void *b)
{
    exchange(a, b);
}

int main() {

    int a = 10;
    int b = 20;
    swap(exchange_int, &a, &b);

    double c = 1.23;
    double d = 2.34;
    swap(exchange_double, &c, &d);

    printf("a = %d, b = %d\n", a, b);
    printf("c = %f, d = %f\n", c, d);

    return 0;
}

