#ifndef OBSERVABLE_MACROS_HPP
#define OBSERVABLE_MACROS_HPP

#define PROCESS_CTOR(X) \
    if (name == "") { \
        var_name =  std::string("tmp") + observer_instance->get_temp_name(); \
    }

// #define PROCESS_COPY_CTOR(X) \
//     if (name == "") { \
//         var_name =  std::string("tmp") + observer_instance->get_temp_name(); \
//     }

// #define PROCESS_MOVE_CTOR(X) \
//     if (name == "") { \
//         var_name =  std::string("tmp") + observer_instance->get_temp_name(); \
//     }

#define CREATE_VAR_VAL(TYPE, NAME, VAL) \
    TYPE NAME(VAL, #NAME)

#define CREATE_VAR(TYPE, NAME) \
    TYPE NAME(#NAME)


// #define COPY_CTOR(TYPE, NAME, VAL) \
//     TYPE NAME(VAL, #NAME)

#define BINARY_OP_PROCESS \
    

#endif