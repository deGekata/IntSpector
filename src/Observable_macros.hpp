#ifndef OBSERVABLE_MACROS_HPP
#define OBSERVABLE_MACROS_HPP

#define PROCESS_CTOR(X) \
    graph_id = observer_instance->var_count++;\
    if (name == "") { \
        var_name =  std::string("tmp") + observer_instance->get_temp_name(); \
        observer_instance->m_logger->createNode(this, "red"); \
    } else { \
        var_name = name; \
        observer_instance->m_logger->createNode(this, "darkgreen"); \
    }\

#define PROCESS_COPY_CTOR(X) \
    {\
        if (name == "") { \
            var_name =  std::string("tmp") + observer_instance->get_temp_name(); \
            observer_instance->m_logger->createNode(this, "red"); \
        } else { \
            var_name = name; \
            observer_instance->m_logger->createNode(this, "darkgreen"); \
        }\
        observer_instance->m_logger->createOrientedEdge(other, *this, "red", "COPY", "red");\
        observer_instance->copy_count++;\
        observer_instance->m_logger->inc_copy_cnt();\
    }

#define PROCESS_COPY_ASSIGNMENT\
    {\
        observer_instance->m_logger->createOrientedEdge(other, *this, "red", "COPY", "red");\
        observer_instance->copy_count++;\
        observer_instance->m_logger->inc_copy_cnt();\
    }


#define PROCESS_MOVE_CTOR(X) \
    {\
        if (name == "") { \
            var_name =  std::string("tmp") + observer_instance->get_temp_name(); \
            observer_instance->m_logger->createNode(this, "red"); \
        } else { \
            var_name = name; \
            observer_instance->m_logger->createNode(this, "darkgreen"); \
        }\
        observer_instance->m_logger->createOrientedEdge(other, *this, "darkgreen", "MOVE", "darkgreen");\
        observer_instance->move_count++;\
        observer_instance->m_logger->inc_move_cnt();\
    }

#define PROCESS_MOVE_ASSIGNMENT\
    {\
        observer_instance->m_logger->createOrientedEdge(other, *this, "darkgreen", "MOVE", "darkgreen");\
        observer_instance->move_count++;\
        observer_instance->m_logger->inc_move_cnt();\
    }


#define CREATE_VAR_VAL(TYPE, NAME, VAL) \
    TYPE NAME(VAL, #NAME)

#define CREATE_VAR(TYPE, NAME) \
    TYPE NAME(#NAME)



// #define COPY_CTOR(TYPE, NAME, VAL) 
//     TYPE NAME(VAL, #NAME)

#define BINARY_OP_PROCESS(result) \
    this->observer_instance->m_logger->createOperationNode(*this, other, result, __FUNCTION__);
    
#define BINARY_OP_ASSIGNMENT_PROCESS \
    this->version++;\
    this->observer_instance->m_logger->createModificationNode(*this, other, __FUNCTION__); 


#define UNARY_OP_PROCESS \
    

#define TRACK_FUNCTION_CALL \
    GraphvizEnvTracker object_unique_name_848481(Location_t __LOCATION__);

#endif


#define ALLOW_COPY_SEMANTICS
#define ASSIGNMENT_OPERATOR_OPTIMIZATION



