#include <stdio.h>

/**
 * ============================================
 *  使用C语言模拟面向对象的继承机制
 *  C语言中没有class、继承等面向对象语法，
 *  但可以通过结构体嵌套 + 函数指针来模拟。
 * ============================================
 */

/**
 * 【基类】 shape（形状）
 * 相当于面向对象中的"基类/父类"。
 * 它包含：
 *  - width / height：数据成员（属性）
 *  - setWidth / setHeight：函数指针（方法）
 *
 * 函数指针的存在，使得我们可以像C++那样：
 *   对象.方法名(参数) 来调用函数
 */
struct shape {
    int width;   // 宽度
    int height;  // 高度

    // 函数指针：指向设置宽度的函数
    void (*setWidth)(struct shape* s, int w);
    // 函数指针：指向设置高度的函数
    void (*setHeight)(struct shape* s, int h);
};

/**
 * setWidth 的实现函数
 * 参数 s：指向 shape 结构体的指针（相当于C++中的 this 指针）
 * 参数 w：要设置的宽度值
 *
 * static 关键字限制该函数只在当前编译单元可见
 */
static void shape_setWidth(struct shape* s, int w)
{
    s->width = w;
}

/**
 * setHeight 的实现函数
 * 参数 s：指向 shape 结构体的指针（相当于C++中的 this 指针）
 * 参数 h：要设置的高度值
 */
static void shape_setHeight(struct shape* s, int h)
{
    s->height = h;
}

/**
 * 【派生类】 rectangle（矩形）
 * 相当于面向对象中的"派生类/子类"。
 * 它包含：
 *  - base（struct shape 类型）：继承自基类的"数据 + 方法"
 *    → 这就是C语言中实现"继承"的核心技巧：结构体嵌套
 *  - getArea：函数指针，派生类新增的方法
 *
 * 内存布局示意：
 *   ┌─────────────────┐
 *   │  base.width     │  ← 继承自shape
 *   │  base.height    │  ← 继承自shape
 *   │  base.setWidth  │  ← 继承自shape（函数指针）
 *   │  base.setHeight │  ← 继承自shape（函数指针）
 *   │  getArea        │  ← 派生类新增（函数指针）
 *   └─────────────────┘
 */
struct rectangle {
    struct shape base;   // 内嵌基类结构体 → 实现"继承"
    int (*getArea)(struct shape* s);  // 派生类新增的方法
};

/**
 * getArea 的实现函数
 * 计算矩形的面积 = 宽度 × 高度
 * 参数 s：指向 shape 的指针（传入 &rect.base 调用）
 */
static int rect_getArea(struct shape* s) {
    return (s->width * s->height);
}

int main() {
    // 创建"派生类"对象 rect
    struct rectangle rect;

    /**
     * 【手动绑定虚函数表（vtable）】
     * 在C++中，编译期会自动建立虚函数表，将函数与对象关联。
     * 在C语言中，我们需要手动将函数指针指向具体的实现函数。
     * 这就是为什么C语言模拟的"多态"需要额外的手动初始化步骤。
     */
    // 将基类的setWidth函数指针绑定到具体实现
    rect.base.setWidth = shape_setWidth;
    // 将基类的setHeight函数指针绑定到具体实现
    rect.base.setHeight = shape_setHeight;
    // 将派生类的getArea函数指针绑定到具体实现
    rect.getArea = rect_getArea;

    /**
     * 【调用"继承"来的方法】
     * 通过 rect.base.setWidth 调用基类的设置宽度函数
     * 传入 &rect.base 作为 this 指针
     * 效果等效于 C++ 中的 rect.setWidth(5)
     */
    rect.base.setWidth(&rect.base, 5);   // 设置宽度为 5
    rect.base.setHeight(&rect.base, 7);  // 设置高度为 7

    /**
     * 【调用"派生类"自身的方法】
     * 计算矩形面积并打印结果
     * 输出：Total area : 35
     */
    printf("Total area : %d\n", rect.getArea(&rect.base));

    return 0;
}