// 使用 C 语言模拟面向对象的封装（Encapsulation）
// 核心思路：将数据和操作数据的方法放在同一结构体中，实现封装

#include <string.h>
#include <stdio.h>

// person 结构体 - 模拟面向对象中的"类"
struct person
{
    char name[12];                                  // 成员变量：姓名
    int age;                                        // 成员变量：年龄
    void (*get_name)(struct person *p, char *name); // 成员函数：获取姓名
    void (*get_age)(struct person *p, int *age);    // 成员函数：获取年龄
};

// get_name - "成员函数"的实现
static void get_name(struct person *p, char *name)
{
    strcpy(name, p->name);
}

// get_age - "成员函数"的实现
static void get_age(struct person *p, int *age)
{
    *age = p->age;
}

// 全局对象 p1 - 模拟"实例化"一个对象
static struct person p1 = {
    .name = "cai",
    .age = 10,
    .get_name = get_name, // 绑定函数到函数指针
    .get_age = get_age,   // 绑定函数到函数指针
};

// 主函数 - 演示 C 语言中的封装概念
int main()
{
    char name[12] = {0}; // 输出缓冲区，全部初始化为 0
    int age = 0;         // 存放年龄的变量

    struct person *p = &p1; // 指针 p 指向全局对象 p1

    // 通过函数指针调用方法
    p->get_name(p, name); // 调用 get_name，结果存入 name 数组
    p->get_age(p, &age);  // 调用 get_age，结果通过 age 指针返回

    printf("name is %s, age = %d \n", name, age);

    return 0;
}