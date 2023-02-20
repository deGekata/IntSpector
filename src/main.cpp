#include <iostream>
#include "my_int.hpp"
#include "my_int_copy.hpp"
MyInt test0(MyInt& a, MyInt& b) {
    TRACK_FUNCTION_CALL
    return a+b;
}

MyInt test1(MyInt& a, MyInt& b) {
    TRACK_FUNCTION_CALL
    CREATE_VAR_VAL(My_Int2, d, 5);
    CREATE_VAR_VAL(My_Int2, m, 5);
    d+m;
    return test0(a, b);
}

int main() {
    std::cout << &__FILE__[get_file_name_offset(__FILE__)];
    TRACK_FUNCTION_CALL
    CREATE_VAR_VAL(MyInt, a, 5);
    CREATE_VAR_VAL(MyInt, b, 10);
    CREATE_VAR_VAL(MyInt, c, 10);
    test1(a, b);
    a = MyInt(10);
    CREATE_VAR_VAL(MyInt, f, MyInt(10));
    CREATE_VAR_VAL(My_Int2, d, 5);

    // a = b;
    // a+b+c;
    // a+b-c;
    // MyInt d(a, "abc");
    // d = a;
    // std::cout << a.get_full_info();
    std::cout << "\nExecuted successfully!\n";
    return 0;
}