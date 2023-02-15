#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP
#include <string>
#include <iostream>
#include "Utilities.hpp"
#include "Observable_macros.hpp"
#include "Graphviz/Graphviz.hpp"
#include <typeinfo>
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

#define ALLOW_COPY_SEMANTICS
#define ALLOW_MOVE_SEMANTICS
#define ASSIGNMENT_OPERATOR_OPTIMIZATION

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
    static std::string class_name;
    // static EventManager manager;
    
protected:
    Observer(){
        m_logger = new GraphvizLogger(std::string(typeid(T).name()) + ".dot");
        
    };//implement constructor
    Observer(const Observer<T>&) = default;
    Observer<T>& operator=(Observer<T>&) = default;
    ~Observer(){
        
        delete m_logger;
    }; //implement destructor

    friend class ObserverDestroyer<T>;
public:
    int tmp_count = 0;
    int var_count = 0;
    int copy_count = 0;
    int move_count = 0;
    static GraphvizLogger* m_logger;
    
    static Observer<T>& getInstance();
    
    static void set_class_name(std::string name) {
        static bool is_set = false;
        if (!is_set) {
            class_name = name;
            is_set = true;
        }
    }

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
std::string Observer<T>::class_name = "";

template <class T>
GraphvizLogger* Observer<T>::m_logger = NULL;

template <class T> 
class Observable : public Graph_object_t {
public:
    Observer<T>* observer_instance;
    Observable() {
        // Observer<T>::set_class_name(this->get_class_name());
        observer_instance = &Observer<T>::getInstance();

    }

    void set_name(char* name) {
        var_name = name;
    }

    std::string get_full_info() {
        return std::string(typeid(T).name()) + " " + var_name + "(" + num_to_hex((uint64_t)this) + ")";
    }
    
    static std::string observable_class_name;
    static size_t id;
    // std::string var_name = "";
};




#endif
