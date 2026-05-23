// C 语言弱符号（Weak Symbol）模拟函数重载
// 演示弱符号函数的使用

#include <stdio.h>

// 弱符号函数，默认实现
void __attribute__((weak)) config(void)
{
    printf("config default\n");
}

// 主函数 - 演示弱符号被强符号覆盖的行为
int main()
{
    config(); // 输出 "config one" —— 强符号覆盖了弱符号
    return 0;
}