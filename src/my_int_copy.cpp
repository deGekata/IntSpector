#include "my_int_copy.hpp"

#include <iostream>



My_Int2::My_Int2(int val, std::string name) {
    // std::cout << this->get_class_name();
    m_value = val;
    PROCESS_CTOR(name);
}

#ifdef ALLOW_COPY_SEMANTICS
My_Int2::My_Int2(const My_Int2& other, std::string name) {
    PROCESS_COPY_CTOR(name);
    m_value = other.m_value;
}

My_Int2& My_Int2::operator=(const My_Int2& other) {
    // PROCESS_COPY_CTOR(name);
    m_value = other.m_value;
    PROCESS_COPY_ASSIGNMENT;
    return *this;
}
#endif

#ifdef ALLOW_MOVE_SEMANTICS
My_Int2::My_Int2(My_Int2&& other, std::string name) {
    m_value = other.m_value;
    other.m_value = INT_MAX;
    PROCESS_MOVE_CTOR(name);
}

My_Int2& My_Int2::operator=(My_Int2&& other) {
    m_value = other.m_value;
    PROCESS_MOVE_ASSIGNMENT;
    return *this;
}

#endif

#ifndef ASSIGMENT_OPERATOR_OPTIMIZATION
    #define BINARY_OPERATOR_PATTERN(op)                     \
    My_Int2 My_Int2::operator op(const My_Int2& other) const {    \
        My_Int2 result(this->m_value op other.m_value);       \
        BINARY_OP_PROCESS(result)                           \
        return result;                                      \
    }
#else 
    #define BINARY_OPERATOR_PATTERN(op)                     \
    My_Int2 My_Int2::operator op(My_Int2 other) const {           \
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
// My_Int2 My_Int2::operator=(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator+(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator-(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator*(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator/(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator%(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator^(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator&(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator|(const My_Int2& other)  const {}
// My_Int2 My_Int2::operator<<(const My_Int2& other) const {}
// My_Int2 My_Int2::operator>>(const My_Int2& other) const {}

My_Int2 My_Int2::operator~()                    const {}
My_Int2& My_Int2::operator+=(const My_Int2& other)  {}
My_Int2& My_Int2::operator-=(const My_Int2& other)  {}
My_Int2& My_Int2::operator*=(const My_Int2& other)  {}
My_Int2& My_Int2::operator/=(const My_Int2& other)  {}
My_Int2& My_Int2::operator%=(const My_Int2& other)  {}
My_Int2& My_Int2::operator^=(const My_Int2& other)  {}
My_Int2& My_Int2::operator&=(const My_Int2& other)  {}
My_Int2& My_Int2::operator|=(const My_Int2& other)  {}
My_Int2& My_Int2::operator<<=(const My_Int2& other) {}
My_Int2& My_Int2::operator>>=(const My_Int2& other) {}

