#include "my_int.hpp"

#include <iostream>



MyInt::MyInt(int val, std::string name) {
    // std::cout << this->get_class_name();
    m_value = val;
    PROCESS_CTOR(name);
}

#ifdef ALLOW_COPY_SEMANTICS
MyInt::MyInt(const MyInt& other, std::string name) {
    PROCESS_COPY_CTOR(name);
    m_value = other.m_value;
}

MyInt& MyInt::operator=(const MyInt& other) {
    // PROCESS_COPY_CTOR(name);
    m_value = other.m_value;
    BINARY_OP_ASSIGNMENT_PROCESS;
    return *this;
}
#endif

#ifdef ALLOW_MOVE_SEMANTICS
MyInt::MyInt(MyInt&& other, std::string name) {
    m_value = other.m_value;
    other.m_value = INT_MAX;
    PROCESS_MOVE_CTOR(name);
}

MyInt& MyInt::operator=(MyInt&& other) {
    m_value = other.m_value;
    PROCESS_MOVE_ASSIGNMENT;
    return *this;
}

#endif

#ifndef ASSIGMENT_OPERATOR_OPTIMIZATION
    #define BINARY_OPERATOR_PATTERN(op)                     \
    MyInt MyInt::operator op(const MyInt& other) const {    \
        MyInt result(this->m_value op other.m_value);       \
        BINARY_OP_PROCESS(result)                           \
        return result;                                      \
    }
#else 
    #define BINARY_OPERATOR_PATTERN(op)                     \
    MyInt MyInt::operator op(MyInt other) const {           \
    other op ## = *this;                                    \
    BINARY_OP_PROCESS(other)                                \
    return other;                                           \
}
#endif

BINARY_OPERATOR_PATTERN(+);
BINARY_OPERATOR_PATTERN(-);
BINARY_OPERATOR_PATTERN(*);
BINARY_OPERATOR_PATTERN(/);
BINARY_OPERATOR_PATTERN(%);
BINARY_OPERATOR_PATTERN(^);
BINARY_OPERATOR_PATTERN(&);
BINARY_OPERATOR_PATTERN(|);
BINARY_OPERATOR_PATTERN(<<);
BINARY_OPERATOR_PATTERN(>>);

#undef BINARY_OPERATOR_PATTERN
// MyInt MyInt::operator=(const MyInt& other)  const {}
// MyInt MyInt::operator+(const MyInt& other)  const {}
// MyInt MyInt::operator-(const MyInt& other)  const {}
// MyInt MyInt::operator*(const MyInt& other)  const {}
// MyInt MyInt::operator/(const MyInt& other)  const {}
// MyInt MyInt::operator%(const MyInt& other)  const {}
// MyInt MyInt::operator^(const MyInt& other)  const {}
// MyInt MyInt::operator&(const MyInt& other)  const {}
// MyInt MyInt::operator|(const MyInt& other)  const {}
// MyInt MyInt::operator<<(const MyInt& other) const {}
// MyInt MyInt::operator>>(const MyInt& other) const {}

#define UNARY_OPERATOR_PATTERN(op)                     \
MyInt& MyInt::operator op(const MyInt& other) const {    \
    MyInt result(this->m_value op other.m_value);       \
    BINARY_OP_PROCESS                                   \
    return result;                                      \
}


#define BINARY_OPERATOR_PATTERN(op)                     \
MyInt& MyInt::operator op(const MyInt& other)  {    \
    this->m_value op other.m_value;       \
    BINARY_OP_ASSIGNMENT_PROCESS                           \
    return *this;                                      \
}



BINARY_OPERATOR_PATTERN(+=);
BINARY_OPERATOR_PATTERN(-=);
BINARY_OPERATOR_PATTERN(*=);
BINARY_OPERATOR_PATTERN(/=);
BINARY_OPERATOR_PATTERN(%=);
BINARY_OPERATOR_PATTERN(^=);
BINARY_OPERATOR_PATTERN(&=);
BINARY_OPERATOR_PATTERN(|=);
BINARY_OPERATOR_PATTERN(<<=);
BINARY_OPERATOR_PATTERN(>>=);

