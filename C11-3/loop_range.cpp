#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // 设置控制台支持 UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    
    std::cout << "=== C++11 Range-based For Loop Examples ===\n\n";

    // 1. 基本数组遍历
    std::cout << "1. Basic array traversal:\n";
    int arr[] = {1, 2, 3, 4, 5};
    
    std::cout << "   Traditional for loop: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    std::cout << "   Range-based for loop: ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 2. std::vector 遍历
    std::cout << "2. std::vector traversal:\n";
    std::vector<int> vec = {10, 20, 30, 40, 50};
    
    std::cout << "   Read-only (const auto&): ";
    for (const auto& value : vec) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    
    std::cout << "   Copy (auto): ";
    for (auto value : vec) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    
    std::cout << "   Modify (auto&): ";
    for (auto& value : vec) {
        value *= 2;
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 3. std::array 遍历
    std::cout << "3. std::array traversal:\n";
    std::array<double, 4> stdArr = {1.1, 2.2, 3.3, 4.4};
    
    std::cout << "   Values: ";
    for (const auto& value : stdArr) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 4. std::list 遍历
    std::cout << "4. std::list traversal:\n";
    std::list<std::string> strList = {"apple", "banana", "cherry", "date"};
    
    std::cout << "   Strings: ";
    for (const auto& str : strList) {
        std::cout << str << " ";
    }
    std::cout << "\n\n";

    // 5. std::map 遍历 (key-value pairs)
    std::cout << "5. std::map traversal (key-value pairs):\n";
    std::map<int, std::string> idToName = {
        {101, "Alice"},
        {102, "Bob"},
        {103, "Charlie"},
        {104, "Diana"}
    };
    
    std::cout << "   Key-Value pairs:\n";
    for (const auto& pair : idToName) {
        std::cout << "     ID: " << pair.first << ", Name: " << pair.second << "\n";
    }
    std::cout << "\n";

    // 6. std::set 遍历
    std::cout << "6. std::set traversal:\n";
    std::set<int> uniqueNumbers = {5, 2, 8, 2, 1, 9, 1}; // 重复元素会被移除
    
    std::cout << "   Unique sorted numbers: ";
    for (const auto& num : uniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // 7. 字符串遍历
    std::cout << "7. String character traversal:\n";
    std::string text = "Hello, C++11!";
    
    std::cout << "   Characters: ";
    for (char c : text) {
        std::cout << "'" << c << "' ";
    }
    std::cout << "\n\n";

    // 8. 初始化列表遍历
    std::cout << "8. Initializer list traversal:\n";
    std::cout << "   Direct iteration: ";
    for (int value : {100, 200, 300, 400}) {
        std::cout << value << " ";
    }
    std::cout << "\n\n";

    // 9. 嵌套容器遍历
    std::cout << "9. Nested container traversal:\n";
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    std::cout << "   Matrix:\n";
    for (const auto& row : matrix) {
        std::cout << "     ";
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // 10. 与算法结合使用
    std::cout << "10. Combined with algorithms:\n";
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 查找偶数
    std::cout << "    Even numbers: ";
    for (const auto& num : numbers) {
        if (num % 2 == 0) {
            std::cout << num << " ";
        }
    }
    std::cout << "\n";
    
    // 计算总和
    int sum = 0;
    for (const auto& num : numbers) {
        sum += num;
    }
    std::cout << "    Sum: " << sum << "\n\n";

    // 11. 类型推导示例
    std::cout << "11. Type deduction examples:\n";
    std::vector<std::pair<int, std::string>> pairs = {
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    
    std::cout << "    Using auto: \n";
    for (const auto& p : pairs) {
        std::cout << "      " << p.first << " -> " << p.second << "\n";
    }
    std::cout << "\n";

    // 12. 修改容器元素
    std::cout << "12. Modifying container elements:\n";
    std::vector<int> modifyVec = {1, 2, 3, 4, 5};
    
    std::cout << "    Original: ";
    for (const auto& val : modifyVec) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    
    // 使用引用修改元素
    for (auto& val : modifyVec) {
        val = val * val; // 平方
    }
    
    std::cout << "    Squared:  ";
    for (const auto& val : modifyVec) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    // 13. 范围for循环的限制和注意事项
    std::cout << "13. Limitations and considerations:\n";
    
    // 不能在循环中修改容器大小
    std::vector<int> safeVec = {1, 2, 3, 4, 5};
    std::cout << "    Safe iteration (read-only): ";
    for (const auto& val : safeVec) {
        std::cout << val << " ";
        // 不要在这里修改容器大小: safeVec.push_back(val * 2);
    }
    std::cout << "\n";
    
    // 如果需要索引，仍然使用传统循环
    std::cout << "    With index (traditional for): ";
    for (size_t i = 0; i < safeVec.size(); ++i) {
        std::cout << "[" << i << "]=" << safeVec[i] << " ";
    }
    std::cout << "\n\n";

    // 14. 自定义类型的范围for循环
    std::cout << "14. Custom type with range-for:\n";
    
    // 简单的自定义容器类
    class SimpleContainer {
    private:
        std::vector<int> data;
    public:
        SimpleContainer(std::initializer_list<int> init) : data(init) {}
        
        // 需要提供 begin() 和 end() 方法
        std::vector<int>::iterator begin() { return data.begin(); }
        std::vector<int>::iterator end() { return data.end(); }
        std::vector<int>::const_iterator begin() const { return data.begin(); }
        std::vector<int>::const_iterator end() const { return data.end(); }
    };
    
    SimpleContainer container{11, 22, 33, 44, 55};
    std::cout << "    Custom container: ";
    for (const auto& val : container) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";

    // 15. 性能对比示例
    std::cout << "15. Performance considerations:\n";
    std::vector<std::string> strings = {"hello", "world", "cpp", "eleven"};
    
    std::cout << "    Efficient (const reference): ";
    for (const auto& s : strings) { // 不会复制字符串
        std::cout << s << " ";
    }
    std::cout << "\n";
    
    std::cout << "    Less efficient (copy): ";
    for (auto s : strings) { // 会复制每个字符串
        std::cout << s << " ";
    }
    std::cout << "\n\n";

    std::cout << "=== Range-based For Loop Examples Complete ===\n";
    
    return 0;
}