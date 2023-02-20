#ifndef MY_INT_HPP
#define MY_INT_HPP

#include <string>
#include <iostream>
#include "Observable.hpp"


class MyInt : public Observable<MyInt>{
public:

    MyInt(int val = 0, std::string name = "");

#ifdef ALLOW_COPY_SEMANTICS
    MyInt(const MyInt& other, std::string name = "");
    MyInt& operator=(const MyInt& other);
#endif

#ifdef ALLOW_MOVE_SEMANTICS
    MyInt(MyInt&& other, std::string name = "");
    MyInt& operator=(MyInt&& other);
// #else
//     MyInt(MyInt&& other, std::string name = "") = delete;
//     MyInt& operator=(MyInt&& other) = delete;
#endif
    
    MyInt operator+(const MyInt& other)  const;
    MyInt operator-(const MyInt& other)  const;
    MyInt operator*(const MyInt& other)  const;
    MyInt operator/(const MyInt& other)  const;
    MyInt operator%(const MyInt& other)  const;
    MyInt operator^(const MyInt& other)  const;
    MyInt operator&(const MyInt& other)  const;
    MyInt operator|(const MyInt& other)  const;
    MyInt operator~()                    const;
    MyInt operator<<(const MyInt& other) const;
    MyInt operator>>(const MyInt& other) const;
    
    MyInt& operator+= (const MyInt& other);
    MyInt& operator-= (const MyInt& other);
    MyInt& operator*= (const MyInt& other);
    MyInt& operator/= (const MyInt& other);
    MyInt& operator%= (const MyInt& other);
    MyInt& operator^= (const MyInt& other);
    MyInt& operator&= (const MyInt& other);
    MyInt& operator|= (const MyInt& other);
    MyInt& operator<<=(const MyInt& other);
    MyInt& operator>>=(const MyInt& other);

    std::string get_value() const override {
        return std::to_string(m_value);
    }

private:
    std::string m_function_name = "";
    
    int m_line_number = 0;
    int m_value = 0;

};





#endif