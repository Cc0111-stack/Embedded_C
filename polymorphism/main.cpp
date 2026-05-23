// 使用 C 语言模拟面向对象的多态（Polymorphism）
// 通过结构体嵌套和函数指针实现多态

#include <string.h>
#include <stdio.h>

// 基类
struct person
{
    char name[12];                                  // 成员变量：姓名
    int age;                                        // 成员变量：年龄
    void (*get_name)(struct person *p, char *name); // 成员函数：获取姓名（相当于虚函数）
};

// 派生类
struct usa_person
{
    struct person p;                                    // 内嵌基类对象（非指针），模拟"继承"
    void (*get_name)(struct usa_person *p, char *name); // 派生类自己的函数指针（重写）
};

// 基类的"默认实现"，同时也是 C 模拟多态的"跳板函数"
static void get_name(struct person *p, char *name)
{
    // 向下转型：将基类指针强制转换为派生类指针
    struct usa_person *child = (struct usa_person *)p;

    // 调用派生类的重写函数（多态分派）
    child->get_name(child, name);
}

// 派生类 usa_person 对 get_name 的"重写"
static void get_usa_name(struct usa_person *p, char *name)
{
    sprintf(name, "%s", p->p.name);             // 从基类成员获取姓名
    sprintf(name + strlen(name), "%s", "-usa"); // 追加后缀
}

static struct usa_person usa_p; // 全局对象（也可以放在堆上）

// 初始化 usa_p 对象
static void init_usa_p()
{
    strcpy(usa_p.p.name, "cai");
    usa_p.p.get_name = get_name;   // 基类的虚函数指针 → 跳板函数
    usa_p.get_name = get_usa_name; // 派生类的重写函数指针 → 实际实现
}

// 主函数 - 演示 C 语言中的多态概念
int main()
{
    init_usa_p();

    char name[12] = {0};
    struct person *p = (struct person *)&usa_p; // 基类指针指向派生类对象（向上转型）

    // 多态调用：表面调用的是 person.get_name，实际执行派生类的函数
    p->get_name(p, name);
    printf("name is %s\n", name);
    return 0;
}