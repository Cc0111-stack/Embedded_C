#include <string.h>
#include <stdio.h>


struct person {
    char name[12];                              // 成员变量：姓名
    int age;                                    // 成员变量：年龄
    void (*get_name)(struct person *p, char *name);   // 成员函数：获取姓名
};

struct usa_person {
    struct person p;                                  // 嵌套结构体（不是指针），实现"继承"
    void (*get_name)(struct usa_person *p, char *name);
};

// 此函数作为 person.get_name 的默认函数（基类行为）
static void get_name(struct person *p, char *name) {
    struct usa_person *child = (struct usa_person *)p;
    child->get_name(p, name);
}

static void get_usa_name(struct usa_person *p, char *name) {
    sprintf(name, "%s", p->p.name);
    sprintf(name + strlen(name), "%s", "-usa");
}

static struct usa_person usa_p;

static void init_usa_p() {
    usa_p.p.name = "cai";
    usa_p.p.get_name = get_name;
    usa_p.get_name = get_usa_name;
}

int main() {
    init_usa_p();

    char name[12] = {0};
    struct person *p = (struct person *)&usa_p;

    p->get_name(p, name);
    printf("name is %s\n", name);
    return 0;
}