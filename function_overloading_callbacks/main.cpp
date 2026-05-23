// 使用 C 语言的函数指针 + 回调模拟"函数重载"
// 通过回调函数实现类似函数重载的功能

#include <stdio.h>

// 交换两个 int 类型变量的值
void exchange_int(void *a, void *b)
{
    int *_a = (int *)a; // 将 void* 转换为 int*
    int *_b = (int *)b; // 将 void* 转换为 int*
    int tmp = 0;

    tmp = *_a; // 保存 a 的值到临时变量
    *_a = *_b; // 将 b 的值赋给 a
    *_b = tmp; // 将临时变量的值赋给 b
}

// 交换两个 double 类型变量的值
void exchange_double(void *a, void *b)
{
    double *_a = (double *)a; // 将 void* 转换为 double*
    double *_b = (double *)b; // 将 void* 转换为 double*
    double tmp = 0;

    tmp = *_a;
    *_a = *_b;
    *_b = tmp;
}

// 统一的函数指针类型（"接口"）
typedef void (*func)(void *, void *);

// 通用交换函数（"重载"的实现者）
void swap(func exchange, void *a, void *b)
{
    exchange(a, b); // 通过函数指针调用实际的交换函数
}

// 主函数 - 演示函数指针实现的函数重载
int main()
{
    int a = 10;
    int b = 20;
    swap(exchange_int, &a, &b);       // 传入 exchange_int 回调
    printf("a = %d, b = %d\n", a, b); // 输出：a = 20, b = 10

    double c = 1.23;
    double d = 2.34;
    swap(exchange_double, &c, &d);    // 传入 exchange_double 回调
    printf("c = %f, d = %f\n", c, d); // 输出：c = 2.34, d = 1.23

    return 0;
}