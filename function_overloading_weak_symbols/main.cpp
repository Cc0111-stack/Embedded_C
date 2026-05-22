#include <stdio.h>

/**
 * ============================================
 *  C 语言弱符号（Weak Symbol）模拟函数重载
 *  ============================================
 *
 *  __attribute__((weak)) 是 GCC 提供的扩展属性。
 *
 *  核心原理：
 *    1. 被 weak 修饰的函数称为"弱符号"（weak symbol）
 *    2. 如果链接时存在同名的"强符号"（普通函数定义），
 *       链接器会选择强符号，忽略弱符号
 *    3. 如果没有强符号，则使用弱符号作为默认实现
 *
 *  典型应用场景：
 *    - 库函数提供默认实现，允许用户覆盖
 *    - 硬件抽象层（HAL）中提供弱符号默认实现，
 *      用户只需定义同名强符号函数即可覆盖
 *    - 嵌入式开发中的 Startup 文件（如 SysTick_Handler 等中断处理函数）
 *
 *  编译说明：
 *    需要将 1.cpp 与 main.cpp 一起编译：
 *      gcc main.cpp 1.cpp -o main
 *    1.cpp 中定义了强符号 config()，
 *    它会覆盖 main.cpp 中的弱符号 config()。
 *    如果只编译 main.cpp，则会使用弱符号的默认实现。
 */

/* weak 修饰——弱符号：当没有强符号时，使用此默认实现 */
void __attribute__((weak)) config(void)
{
    printf("config default\n");
}

int main()
{
    config();   /* 输出 "config one" —— 强符号覆盖了弱符号 */
    return 0;
}
