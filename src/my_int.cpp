#include "my_int.hpp"
#include <iostream>


int MyInt::operator+(const MyInt& other) const {
    return m_value + other.m_value;
}