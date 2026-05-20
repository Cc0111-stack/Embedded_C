
#include <stdio.h>
#include <stdarg.h>

static void va_func(int n, ...)//n是指后面要传入多少个变量
{
    va_list ap;
    va_start(ap, n);
    while (n--) printf("%d \n", va_arg(ap, int));
    va_end(ap);
}


int main() {
    va_func(1, 100);
    va_func(2, 200, 300);


    return 0;
}

