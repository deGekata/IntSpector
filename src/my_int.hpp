#ifndef MY_INT_HPP
#define MY_INT_HPP

#include <string>
#include <iostream>
#include "Observable.hpp"

#define TEST_LEVEL 0

#if TEST_LEVEL == 3 || TEST_LEVEL == 2
    //rnwo
    #define ALLOW_MOVE_SEMANTICS
#endif
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


#if TEST_LEVEL == 0
//here args will be transfered by value
//ans swapped values will be returned by pair
//and no rnwo optimisation
    static MyInt smart_sum_aggregator(MyInt a, MyInt b, MyInt c) {
        TRACK_FUNCTION_CALL
        CREATE_VAR_VAL(MyInt, ret, a + b - c);
        return ret;
    }
#endif

#if TEST_LEVEL == 1
//pass args by reference
//still no rnwo
//no move constructors
    static MyInt smart_sum_aggregator(MyInt& a, MyInt& b, MyInt& c) {
        TRACK_FUNCTION_CALL
        CREATE_VAR_VAL(MyInt, ret, a + b - c);
        return ret;
    }
#endif

#if TEST_LEVEL == 2
    #define ALLOW_MOVE_SEMANTICS
    static MyInt smart_sum_aggregator(MyInt& a, MyInt& b, MyInt& c) {
        TRACK_FUNCTION_CALL
        CREATE_VAR_VAL(MyInt, ret, a + b - c);
        return ret;
    }
//allow move constructors
//no rnwo

#endif

#if TEST_LEVEL == 3
    //rnwo
    #define ALLOW_MOVE_SEMANTICS
    static MyInt smart_sum_aggregator(MyInt& a, MyInt& b, MyInt& c) {
        TRACK_FUNCTION_CALL
        CREATE_VAR_VAL(MyInt, ret, a + b - c);
        return ret;
    }
#endif


static void test_sum_agg() {
    TRACK_FUNCTION_CALL
    CREATE_VAR_VAL(MyInt, a, 14);
    CREATE_VAR_VAL(MyInt, b, 29);
    CREATE_VAR_VAL(MyInt, c, 7);
    CREATE_VAR_VAL(MyInt, res, smart_sum_aggregator(a, b, c));
    return;
}

#endif