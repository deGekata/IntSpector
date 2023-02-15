#ifndef MY_INT2_HPP
#define MY_INT2_HPP

#include <string>
#include <iostream>
#include "Observable.hpp"


class My_Int2 : public Observable<My_Int2>{
public:

    My_Int2(int val = 0, std::string name = "");

#ifdef ALLOW_COPY_SEMANTICS
    My_Int2(const My_Int2& other, std::string name = "");
    My_Int2& operator=(const My_Int2& other);
#endif

#ifdef ALLOW_MOVE_SEMANTICS
    My_Int2(My_Int2&& other, std::string name = "");
    My_Int2& operator=(My_Int2&& other);
#else
    My_Int2(My_Int2&& other, std::string name = "") = delete;
    My_Int2& operator=(My_Int2&& other) = delete;
#endif
    
    My_Int2 operator+(const My_Int2& other)  const;
    My_Int2 operator-(const My_Int2& other)  const;
    My_Int2 operator*(const My_Int2& other)  const;
    My_Int2 operator/(const My_Int2& other)  const;
    My_Int2 operator%(const My_Int2& other)  const;
    My_Int2 operator^(const My_Int2& other)  const;
    My_Int2 operator&(const My_Int2& other)  const;
    My_Int2 operator|(const My_Int2& other)  const;
    My_Int2 operator~()                    const;
    My_Int2 operator<<(const My_Int2& other) const;
    My_Int2 operator>>(const My_Int2& other) const;
    
    My_Int2& operator+= (const My_Int2& other);
    My_Int2& operator-= (const My_Int2& other);
    My_Int2& operator*= (const My_Int2& other);
    My_Int2& operator/= (const My_Int2& other);
    My_Int2& operator%= (const My_Int2& other);
    My_Int2& operator^= (const My_Int2& other);
    My_Int2& operator&= (const My_Int2& other);
    My_Int2& operator|= (const My_Int2& other);
    My_Int2& operator<<=(const My_Int2& other);
    My_Int2& operator>>=(const My_Int2& other);

    std::string get_value() const override {
        return std::to_string(m_value);
    }

private:
    std::string m_function_name = "";
    
    int m_line_number = 0;
    int m_value = 0;

};





#endif