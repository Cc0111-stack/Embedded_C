#include <string.h>
#include <stdio.h>

/**
 * @brief 使用结构体 + 函数指针模拟面向对象封装
 *        将数据（name, age）和操作数据的方法（get_name, get_age）封装在一起
 */
struct person {
    char name[12];                              // 成员变量：姓名
    int age;                                    // 成员变量：年龄
    void (*get_name)(struct person *p, char *name);   // 成员函数：获取姓名
    void (*get_age)(struct person *p, int *age);      // 成员函数：获取年龄
};

/**
 * @brief 获取 person 对象的姓名（相当于 C++ 的成员函数）
 * @param p   指向 person 对象的指针（相当于 this 指针）
 * @param name 输出缓冲区，用于接收姓名
 */
static void get_name(struct person *p, char *name) {
    strcpy(name, p->name);      // 将对象内部的 name 拷贝到输出缓冲区
}

/**
 * @brief 获取 person 对象的年龄
 * @param p   指向 person 对象的指针
 * @param age 输出参数，通过指针返回年龄值
 */
static void get_age(struct person *p, int *age) {
    *age = p->age;              // 将对象内部的 age 通过指针参数返回
}

/**
 * @brief 静态全局的 person 对象，使用指定初始化器初始化
 *        .name / .age      → 初始化成员变量
 *        .get_name / .get_age → 绑定函数指针到具体的实现函数
 */
static struct person p1 = {
    .name = "cai",              // 姓名初始化为 "cai"
    .age = 10,                  // 年龄初始化为 10
    .get_name = get_name,       // 绑定 get_name 函数
    .get_age = get_age,         // 绑定 get_age 函数
};

int main() {
    char name[12] = {0};        // 存放姓名的输出缓冲区，全部初始化为 0
    int age = 0;                // 存放年龄的变量

    struct person *p = &p1;     // 指针 p 指向全局对象 p1

    /* 通过函数指针调用方法，模拟面向对象的 p->getName() 语法 */
    p->get_name(p, name);       // 获取姓名，结果存入 name 数组
    p->get_age(p, &age);        // 获取年龄，结果通过 age 指针返回

    /* 打印结果 */
    printf("name is %s, age = %d \n", name, age);

    return 0;
}