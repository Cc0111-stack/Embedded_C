#include <stdio.h>
//weak修饰的函数属于弱连接函数，当前工程如果有定义相同的函数时，weak修饰的函数会被覆盖
void __attribute__((weak)) config(void)
{
    printf("config default\n");
}

// void config(void)//不知道为什么不行。。。
// {
//     printf("config one");
// }


int main()
{
    config();

    return 0;
}
