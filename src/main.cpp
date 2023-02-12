#include <iostream>
#include "my_int.hpp"

int main() {

    MyInt a;
    // Observer<int>& obs = Observer<int>::getInstance();
    std::cout << a.get_full_info();
    std::cout << "Hello World!";
    return 0;
}