#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP
#include <string>
#include <iostream>
#include "Utilities.hpp"
#include "Observable_macros.hpp"
#define TEST_PRINT(x) std::cout << #x << "'\n";

//{
// template <char... Chars>
// struct String {};

// template <char... Chars>
// String<Chars...> operator""_conststr() {
//   return String<Chars...>();
// }

// template <class S>
// std::string_view GetContent() {
//   return std::string_view(Get<S>::value, sizeof(Get<S>::value));
// }
//}


template <class T>
class Observer;

template <class T>
class ObserverDestroyer {
private:
    Observer<T>* app_instance_ = NULL;
public:
    ~ObserverDestroyer();
    void initialize(Observer<T>* ptr);
};

template <class T>
class Observer {
private:
    static Observer<T>* app_instance_;
    static ObserverDestroyer<T> destroyer;
    // static EventManager manager;
    int tmp_count = 0;
protected:
    Observer(){};//implement constructor
    Observer(const Observer<T>&) = default;
    Observer<T>& operator=(Observer<T>&) = default;
    ~Observer(){}; //implement destructor

    friend class ObserverDestroyer<T>;
public:
    static Observer<T>& getInstance();
    
    static std::string get_temp_name() {
        return std::to_string(getInstance().tmp_count++);
    }
};


template <class T>
ObserverDestroyer<T>::~ObserverDestroyer() {   
    delete app_instance_; 
}

template <class T>
void ObserverDestroyer<T>::initialize(Observer<T>* p) {
    app_instance_ = p; 
}

template <class T>
Observer<T>& Observer<T>::getInstance() {
    if(!app_instance_)     {
        app_instance_ = new Observer<T>();
        destroyer.initialize( app_instance_);     
    }
    return *app_instance_;  
}

template <class T>
Observer<T>* Observer<T>::app_instance_ = 0;

template <class T>
ObserverDestroyer<T> Observer<T>::destroyer;


template <class T> 
class Observable {
public:
    Observer<T>* observer_instance;
    Observable() {
        observer_instance = &Observer<T>::getInstance();
    }

    void set_name(char* name) {
        var_name = name;
    }

    std::string get_full_info() {
        return std::string(get_class_name()) + " " + var_name + "(" + num_to_hex((uint64_t)this) + ")";
    }

    virtual const char* get_class_name() = 0;
    virtual std::string print_value()    = 0;

    std::string class_name = "";
    std::string var_name = "";
};




#endif
