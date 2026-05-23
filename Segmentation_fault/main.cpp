// 段错误（Segmentation Fault）演示程序
// 演示函数指针的基本使用以及可能导致段错误的情况

#include <stdio.h>

// 示例函数 - 用于演示函数指针
void func(void)
{
    printf("func call\n");
}

// 主函数 - 演示函数指针的访问和潜在危险操作
int main(void)
{
    // 打印函数地址
    printf("func address: %p\n", func);

    // 通过函数指针调用函数
    void (*p)(void) = func;
    p(); // 正常调用

    // 将函数地址转换为整型指针（危险操作）
    int *p1 = (int *)func;
    printf("func address: %p\n", *p1);

    // 尝试写入函数代码段（会导致段错误）
    // *p1 = 1; // 注释掉以避免程序崩溃

    return 0;
}