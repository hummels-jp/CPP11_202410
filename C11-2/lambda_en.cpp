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

    // 5. Mixed capture (value a, reference b)
    std::cout << "5. Mixed capture (value a, reference b):\n";
    int a = 100, b = 200;
    auto mixed_capture = [a, &b](int multiplier) {
        b += 10;  // modify b
        return a * multiplier + b;  // a is copy, b is reference
    };
    std::cout << "   Result: " << mixed_capture(2) << "\n";
    std::cout << "   a = " << a << ", b = " << b << "\n\n";

    // 6. Capture all variables
    std::cout << "6. Auto capture:\n";
    int val1 = 50, val2 = 30;
    
    // Capture all by value
    auto capture_all_by_value = [=]() {
        return val1 + val2;
    };
    
    // Capture all by reference
    auto capture_all_by_ref = [&]() {
        val1 += 5;
        val2 += 5;
        return val1 + val2;
    };
    
    std::cout << "   Capture all by value: " << capture_all_by_value() << "\n";
    std::cout << "   Capture all by reference: " << capture_all_by_ref() << "\n";
    std::cout << "   Modified val1 = " << val1 << ", val2 = " << val2 << "\n\n";

    // 7. Using lambda in STL algorithms
    std::cout << "7. Using lambda in STL algorithms:\n";
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Use for_each to print all numbers
    std::cout << "   Original array: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << "\n";
    
    // Use find_if to find first even number
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    if (it != numbers.end()) {
        std::cout << "   First even number: " << *it << "\n";
    }
    
    // Use transform to square all numbers
    std::vector<int> squares(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squares.begin(), [](int n) {
        return n * n;
    });
    std::cout << "   Squared: ";
    for (int sq : squares) {
        std::cout << sq << " ";
    }
    std::cout << "\n";
    
    // Use count_if to count even numbers
    int even_count = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "   Even count: " << even_count << "\n\n";

    // 8. Returning lambda (higher-order function)
    std::cout << "8. Function returning lambda:\n";
    auto make_multiplier = [](int factor) {
        return [factor](int value) {
            return factor * value;
        };
    };
    
    auto times_three = make_multiplier(3);
    auto times_five = make_multiplier(5);
    
    std::cout << "   7 * 3 = " << times_three(7) << "\n";
    std::cout << "   7 * 5 = " << times_five(7) << "\n\n";

    // 9. Using mutable lambda
    std::cout << "9. Mutable lambda:\n";
    int initial_value = 100;
    auto mutable_lambda = [initial_value](int increment) mutable {
        initial_value += increment;
        return initial_value;
    };
    
    std::cout << "   First call: " << mutable_lambda(10) << "\n";
    std::cout << "   Second call: " << mutable_lambda(20) << "\n";
    std::cout << "   Original value unchanged: " << initial_value << "\n\n";

    // 10. Using std::function to store lambda
    std::cout << "10. Using std::function to store lambda:\n";
    std::function<int(int, int)> operation;
    
    // Store addition lambda
    operation = [](int x, int y) { return x + y; };
    std::cout << "    Addition: 15 + 25 = " << operation(15, 25) << "\n";
    
    // Store multiplication lambda
    operation = [](int x, int y) { return x * y; };
    std::cout << "    Multiplication: 15 * 25 = " << operation(15, 25) << "\n\n";

    // 11. Recursive lambda
    std::cout << "11. Recursive lambda (factorial):\n";
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    
    std::cout << "    5! = " << factorial(5) << "\n";
    std::cout << "    7! = " << factorial(7) << "\n\n";

    // 12. More lambda examples with algorithms
    std::cout << "12. More lambda examples with algorithms:\n";
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    
    // Find first word with length > 5
    auto long_word = std::find_if(words.begin(), words.end(), [](const std::string& word) {
        return word.length() > 5;
    });
    
    if (long_word != words.end()) {
        std::cout << "    Word with length > 5: " << *long_word << "\n";
    }
    
    // Calculate total length of all words
    int total_length = std::accumulate(words.begin(), words.end(), 0, 
        [](int sum, const std::string& word) {
            return sum + word.length();
        });
    std::cout << "    Total length of all words: " << total_length << "\n";

    std::cout << "\n=== Lambda Expression Examples Complete ===\n";
    return 0;
}