#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

int main() {
#ifdef _WIN32
    // Set console output to UTF-8 for Windows
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "");
#endif

    std::cout << "=== C++11 Lambda Expression Examples ===\n\n";

    // 1. Basic lambda expression
    std::cout << "1. Basic lambda expression:\n";
    auto basic_lambda = []() {
        return "Hello, Lambda!";
    };
    std::cout << "   " << basic_lambda() << "\n\n";

    // 2. Lambda with parameters
    std::cout << "2. Lambda with parameters:\n";
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "   5 + 3 = " << add(5, 3) << "\n\n";

    // 3. Capture by value
    std::cout << "3. Capture by value:\n";
    int x = 10;
    auto capture_by_value = [x](int y) {
        return x * y;  // x is copied into lambda
    };
    std::cout << "   x * 5 = " << capture_by_value(5) << " (x = " << x << ")\n\n";

    // 4. Capture by reference
    std::cout << "4. Capture by reference:\n";
    int counter = 0;
    auto increment = [&counter]() {
        return ++counter;  // modify external variable
    };
    std::cout << "   Counter: " << increment() << ", " << increment() << ", " << increment() << "\n";
    std::cout << "   External counter = " << counter << "\n\n";

    // 5. 混合捕获
    std::cout << "5. 混合捕获 (按值捕获 a，按引用捕获 b):\n";
    int a = 100, b = 200;
    auto mixed_capture = [a, &b](int multiplier) {
        b += 10;  // 修改 b
        return a * multiplier + b;  // a 是副本，b 是引用
    };
    std::cout << "   结果: " << mixed_capture(2) << "\n";
    std::cout << "   a = " << a << ", b = " << b << "\n\n";

    // 6. 捕获所有变量
    std::cout << "6. 自动捕获:\n";
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
    
    std::cout << "   按值捕获所有: " << capture_all_by_value() << "\n";
    std::cout << "   按引用捕获所有: " << capture_all_by_ref() << "\n";
    std::cout << "   修改后 val1 = " << val1 << ", val2 = " << val2 << "\n\n";

    // 7. 在 STL 算法中使用 lambda
    std::cout << "7. 在 STL 算法中使用 lambda:\n";
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 使用 for_each 打印所有数字
    std::cout << "   原始数组: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << "\n";
    
    // 使用 find_if 查找第一个偶数
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    if (it != numbers.end()) {
        std::cout << "   第一个偶数: " << *it << "\n";
    }
    
    // 使用 transform 将所有数字平方
    std::vector<int> squares(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squares.begin(), [](int n) {
        return n * n;
    });
    std::cout << "   平方后: ";
    for (int sq : squares) {
        std::cout << sq << " ";
    }
    std::cout << "\n";
    
    // 使用 count_if 计算偶数个数
    int even_count = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "   偶数个数: " << even_count << "\n\n";

    // 8. 返回 lambda (高阶函数)
    std::cout << "8. 返回 lambda 的函数:\n";
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
    std::cout << "9. 可变 lambda (mutable):\n";
    int initial_value = 100;
    auto mutable_lambda = [initial_value](int increment) mutable {
        initial_value += increment;
        return initial_value;
    };
    
    std::cout << "   第一次调用: " << mutable_lambda(10) << "\n";
    std::cout << "   第二次调用: " << mutable_lambda(20) << "\n";
    std::cout << "   原始值未变: " << initial_value << "\n\n";

    // 10. 使用 std::function 存储 lambda
    std::cout << "10. 使用 std::function 存储 lambda:\n";
    std::function<int(int, int)> operation;
    
    // 存储加法 lambda
    operation = [](int x, int y) { return x + y; };
    std::cout << "    加法: 15 + 25 = " << operation(15, 25) << "\n";
    
    // 存储乘法 lambda
    operation = [](int x, int y) { return x * y; };
    std::cout << "    乘法: 15 * 25 = " << operation(15, 25) << "\n\n";

    // 11. 递归 lambda
    std::cout << "11. 递归 lambda (阶乘):\n";
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    
    std::cout << "    5! = " << factorial(5) << "\n";
    std::cout << "    7! = " << factorial(7) << "\n\n";

    // 12. 泛型 lambda (C++14 特性的预览，使用 auto 参数)
    std::cout << "12. Lambda 与算法结合的更多示例:\n";
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    
    // 查找长度大于5的第一个单词
    auto long_word = std::find_if(words.begin(), words.end(), [](const std::string& word) {
        return word.length() > 5;
    });
    
    if (long_word != words.end()) {
        std::cout << "    长度>5的单词: " << *long_word << "\n";
    }
    
    // 计算所有单词的总长度
    int total_length = std::accumulate(words.begin(), words.end(), 0, 
        [](int sum, const std::string& word) {
            return sum + word.length();
        });
    std::cout << "    所有单词总长度: " << total_length << "\n";

    std::cout << "\n=== Lambda 表达式示例结束 ===\n";
    return 0;
}