#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // 设置控制台支持 UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    
    std::cout << u8"=== C++11 Lambda 表达式示例 ===\n\n";

    // 1. 基本 lambda 表达式
    std::cout << u8"1. 基本 lambda 表达式:\n";
    auto basic_lambda = []() {
        return "Hello, Lambda!";
    };
    std::cout << "   " << basic_lambda() << "\n\n";

    // 2. 带参数的 lambda
    std::cout << u8"2. 带参数的 lambda:\n";
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "   5 + 3 = " << add(5, 3) << "\n\n";

    // 3. 捕获局部变量 (按值捕获)
    std::cout << u8"3. 按值捕获局部变量:\n";
    int x = 10;
    auto capture_by_value = [x](int y) {
        return x * y;  // x 被复制到 lambda 中
    };
    std::cout << "   x * 5 = " << capture_by_value(5) << " (x = " << x << ")\n\n";

    // 4. 按引用捕获
    std::cout << u8"4. 按引用捕获:\n";
    int counter = 0;
    auto increment = [&counter]() {
        return ++counter;  // 修改外部变量
    };
    std::cout << u8"   计数器: " << increment() << ", " << increment() << ", " << increment() << "\n";
    std::cout << u8"   外部 counter = " << counter << "\n\n";

    // 5. 混合捕获
    std::cout << u8"5. 混合捕获 (按值捕获 a，按引用捕获 b):\n";
    int a = 100, b = 200;
    auto mixed_capture = [a, &b](int multiplier) {
        b += 10;  // 修改 b
        return a * multiplier + b;  // a 是副本，b 是引用
    };
    std::cout << u8"   结果: " << mixed_capture(2) << "\n";
    std::cout << "   a = " << a << ", b = " << b << "\n\n";

    // 6. 捕获所有变量
    std::cout << u8"6. 自动捕获:\n";
    int val1 = 50, val2 = 30;
    
    // 按值捕获所有变量
    auto capture_all_by_value = [=]() {
        return val1 + val2;
    };
    
    // 按引用捕获所有变量
    auto capture_all_by_ref = [&]() {
        val1 += 5;
        val2 += 5;
        return val1 + val2;
    };
    
    std::cout << u8"   按值捕获所有: " << capture_all_by_value() << "\n";
    std::cout << u8"   按引用捕获所有: " << capture_all_by_ref() << "\n";
    std::cout << u8"   修改后 val1 = " << val1 << ", val2 = " << val2 << "\n\n";

    // 7. 在 STL 算法中使用 lambda
    std::cout << u8"7. 在 STL 算法中使用 lambda:\n";
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 使用 for_each 打印所有数字
    std::cout << u8"   原始数组: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << "\n";
    
    // 使用 find_if 查找第一个偶数
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    if (it != numbers.end()) {
        std::cout << u8"   第一个偶数: " << *it << "\n";
    }
    
    // 使用 transform 将所有数字平方
    std::vector<int> squares(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squares.begin(), [](int n) {
        return n * n;
    });
    std::cout << u8"   平方后: ";
    for (int sq : squares) {
        std::cout << sq << " ";
    }
    std::cout << "\n";
    
    // 使用 count_if 计算偶数个数
    int even_count = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << u8"   偶数个数: " << even_count << "\n\n";

    // 8. 返回 lambda (高阶函数)
    std::cout << u8"8. 返回 lambda 的函数:\n";
    auto make_multiplier = [](int factor) {
        return [factor](int value) {
            return factor * value;
        };
    };
    
    auto times_three = make_multiplier(3);
    auto times_five = make_multiplier(5);
    
    std::cout << "   7 * 3 = " << times_three(7) << "\n";
    std::cout << "   7 * 5 = " << times_five(7) << "\n\n";

    // 9. 使用 mutable lambda
    std::cout << u8"9. 可变 lambda (mutable):\n";
    int initial_value = 100;
    auto mutable_lambda = [initial_value](int increment) mutable {
        initial_value += increment;
        return initial_value;
    };
    
    std::cout << u8"   第一次调用: " << mutable_lambda(10) << "\n";
    std::cout << u8"   第二次调用: " << mutable_lambda(20) << "\n";
    std::cout << u8"   原始值未变: " << initial_value << "\n\n";

    // 10. 使用 std::function 存储 lambda
    std::cout << u8"10. 使用 std::function 存储 lambda:\n";
    std::function<int(int, int)> operation;
    
    // 存储加法 lambda
    operation = [](int x, int y) { return x + y; };
    std::cout << u8"    加法: 15 + 25 = " << operation(15, 25) << "\n";
    
    // 存储乘法 lambda
    operation = [](int x, int y) { return x * y; };
    std::cout << u8"    乘法: 15 * 25 = " << operation(15, 25) << "\n\n";

    // 11. 递归 lambda
    std::cout << u8"11. 递归 lambda (阶乘):\n";
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    
    std::cout << "    5! = " << factorial(5) << "\n";
    std::cout << "    7! = " << factorial(7) << "\n\n";

    // 12. Lambda 与算法结合的更多示例
    std::cout << u8"12. Lambda 与算法结合的更多示例:\n";
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    
    // 查找长度大于5的第一个单词
    auto long_word = std::find_if(words.begin(), words.end(), [](const std::string& word) {
        return word.length() > 5;
    });
    
    if (long_word != words.end()) {
        std::cout << u8"    长度>5的单词: " << *long_word << "\n";
    }
    
    // 计算所有单词的总长度
    int total_length = std::accumulate(words.begin(), words.end(), 0, 
        [](int sum, const std::string& word) {
            return sum + word.length();
        });
    std::cout << u8"    所有单词总长度: " << total_length << "\n";

    std::cout << u8"\n=== Lambda 表达式示例结束 ===\n";
    return 0;
}