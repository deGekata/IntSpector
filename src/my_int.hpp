#ifndef MY_INT_HPP
#define MY_INT_HPP

#include <string>
#include <iostream>
#include "Observable.hpp"


class MyInt : public Observable<MyInt>{
public:
    // MyInt() : Observable<MyInt>() {
    //     std::cout << "MyInt default constructor called" << std::endl;
    // }

    MyInt(std::string name) {
        PROCESS_CTOR(name);
    }

    MyInt(int val, std::string name = "") {
        PROCESS_CTOR(name);
        m_value = val;
    }
    

    int operator+(const MyInt& other)  const;
    int operator-(const MyInt& other)  const;
    int operator*(const MyInt& other)  const;
    int operator/(const MyInt& other)  const;
    int operator%(const MyInt& other)  const;
    int operator^(const MyInt& other)  const;
    int operator&(const MyInt& other)  const;
    int operator|(const MyInt& other)  const;
    int operator~()                    const;
    int operator<<(const MyInt& other) const;
    int operator>>(const MyInt& other) const;
    
    int operator+=(const MyInt& other);
    int operator-=(const MyInt& other);
    int operator*=(const MyInt& other);
    int operator/=(const MyInt& other);
    int operator%=(const MyInt& other);
    int operator^=(const MyInt& other);
    int operator&=(const MyInt& other);
    int operator|=(const MyInt& other);
    int operator<<=(const MyInt& other);
    int operator>>=(const MyInt& other);
    
    const char* get_class_name() override {
        return "MyInt";
    }
private:
    std::string m_function_name = "";
    
    int m_line_number = 0;
    int m_value = 0;

};




#endif