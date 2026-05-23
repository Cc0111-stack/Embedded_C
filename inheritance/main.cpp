// 使用 C 语言模拟面向对象的继承（Inheritance）
// 通过结构体嵌套实现继承

#include <stdio.h>

// 【基类】 shape（形状）
struct shape
{
    int width;  // 宽度
    int height; // 高度

    // 函数指针：设置宽度
    void (*setWidth)(struct shape *s, int w);

    // 函数指针：设置高度
    void (*setHeight)(struct shape *s, int h);
};

// 基类 setWidth 的实现
static void shape_setWidth(struct shape *s, int w)
{
    s->width = w;
}

// 基类 setHeight 的实现
static void shape_setHeight(struct shape *s, int h)
{
    s->height = h;
}

// 【派生类】 rectangle（矩形）
struct rectangle
{
    struct shape base;               // 内嵌基类对象 → 实现"继承"
    int (*getArea)(struct shape *s); // 派生类新增的方法：计算面积
};

// 派生类新增方法 getArea 的实现
static int rect_getArea(struct shape *s)
{
    return (s->width * s->height);
}

// 主函数 - 演示 C 语言中的继承概念
int main()
{
    // 创建"派生类"对象 rect
    struct rectangle rect;

    // 手动绑定函数指针——模拟 vtable 初始化
    rect.base.setWidth = shape_setWidth;   // 将基类的 setWidth 函数指针绑定到具体实现
    rect.base.setHeight = shape_setHeight; // 将基类的 setHeight 函数指针绑定到具体实现
    rect.getArea = rect_getArea;           // 将派生类的 getArea 函数指针绑定到具体实现

    // 调用"继承"来的方法
    rect.base.setWidth(&rect.base, 5);  // 设置宽度为 5
    rect.base.setHeight(&rect.base, 7); // 设置高度为 7

    // 调用"派生类"自身的方法
    printf("Total area : %d\n", rect.getArea(&rect.base)); // 计算并输出面积

    return 0;
}