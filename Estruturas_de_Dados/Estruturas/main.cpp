
#include <string>
#include <vector>
#include <iostream>

#include "AVLTree.h"

template <typename T, typename U>
void simple_insertion(T& list, U& values) {
    if (list.empty()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    list.insert(values[0]);
    if(!list.empty()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    if (1 == list.size()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
}


template <typename T, typename U>
void multiple_insertion(T& list, const U& values) {
    if (list.empty()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    for (auto& value : values) {
        list.insert(value);
    }
    if (!list.empty()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    if (values.size() == list.size()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
}

template <typename T, typename U>
void contains_all(const T& list, const U& values) {
    for (auto& value : values) {
        if (list.contains(value)) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    }
}

int main(int argc, char* argv[]) {
    const auto int_values = std::vector<int>{
        10, 5, 8, 20, 25, 15, -5, -10, 30, -15
    };
    structures::AVLTree<int> int_list{};
    
    const auto string_values = std::vector<std::string>{
        "AAA", "BBB", "123", "Hello, World!", "Goodbye, World!"
    };
    structures::AVLTree<std::string> string_list{};

    return 0;
}
