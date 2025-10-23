#include <stdio.h>

// .data 节中的变量
int initialized_global = 42;              // 已初始化全局变量
static int static_initialized = 100;      // 已初始化静态全局变量
const int const_initialized = 200;        // 已初始化常量
char message[] = "Data section example";  // 已初始化字符数组

// .bss 节中的变量（作为对比）
int uninitialized_global;                 // 未初始化全局变量
static int static_uninitialized;          // 未初始化静态变量

void demo_function() {
    // 静态局部变量 - 存放在 .data 节
    static int function_static = 0;
    function_static++;
    printf("Function static: %d\n", function_static);
    
    // 自动变量 - 存放在栈上
    int local_auto = 5;
}

int main() {
    printf("初始化的全局变量: %d\n", initialized_global);
    printf("静态初始化的全局变量: %d\n", static_initialized);
    printf("常量: %d\n", const_initialized);
    printf("消息: %s\n", message);
    
    demo_function();
    demo_function();
    demo_function();
    
    return 0;
}
