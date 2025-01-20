#include "../exercise.h"

// READ: 数组 <https://zh.cppreference.com/w/cpp/language/array>

static unsigned long long cache[90]{0, 1};
static int cached = 2;
unsigned long long fibonacci(int i) {
    for (; cached <= i; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2]; 
        // std::cout << "fibonacci(" << cached << ") = " << cache[cached] << std::endl;  
    }
    return cache[i];
}

int main(int argc, char **argv) {
    // TODO: 为此 ASSERT 填写正确的值
    // std::cout << sizeof(cache);
    ASSERT(sizeof(cache) == 720, "sizeof array is size of all its elements");
    // ---- 不要修改以下代码 ----
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(20) == 6765, "fibonacci(20) should be 6765");
    ASSERT(fibonacci(80) == 23416728348467685, "fibonacci(80) should be 23416728348467685");
    return 0;
}
