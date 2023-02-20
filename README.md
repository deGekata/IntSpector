## Shallow Copy vs. Deep Copy

When working with objects in programming, it's important to understand the difference between a shallow copy and a deep copy.

A shallow copy creates a new object that points to the same memory location as the original object. This means that changes made to the new object will also affect the original object, and vice versa. In other words, the new object is just a reference to the original object.

A deep copy, on the other hand, creates a new object with a new memory location that is an exact replica of the original object. This means that changes made to the new object will not affect the original object, and vice versa. In other words, the new object is completely separate from the original object.

## Move Semantics and Difference Between Move and Copy Constructors

Move semantics is a C++ feature that allows objects to be moved rather than copied. This is useful in situations where a copy of an object is expensive in terms of time or memory.

A move constructor is a special constructor that creates a new object by moving the resources of an existing object. This means that the new object takes ownership of the resources of the old object, and the old object becomes null or empty. Move constructors are typically faster than copy constructors, because they don't have to allocate new memory and copy the existing object.

A copy constructor, on the other hand, creates a new object by copying the resources of an existing object. This means that the new object has its own copy of the resources, and the old object is left unchanged.

The main difference between a move constructor and a copy constructor is that a move constructor transfers ownership of the resources, while a copy constructor creates a new copy of the resources.

## Here is some information about existing types of constructors by "sample" object
`T(T&)`: This is a non-const copy constructor that creates a new object by copying the contents of an existing object. The parameter passed to this constructor is a non-const reference to the object being copied, which allows the constructor to modify the object if necessary. In some situations it might be counter-intuitive, that COPY constructor modify reference, so there are very few cases of use, where it can be implemented this way.

`T(const T&)`: This is a const copy constructor that creates a new object by copying the contents of an existing object. The parameter passed to this constructor is a const reference to the object being copied, which means that the constructor cannot modify the object.

`T(T&&)`: This is a move constructor that creates a new object by "stealing" the contents of an existing object. The parameter passed to this constructor is an rvalue reference to the object being moved, which allows the constructor to efficiently transfer ownership of the object's resources without making a copy.

`T(const T&&)`: I fear no man... But that thing... it scares me








## Situations Where Move Constructor Can't/Shouldn't be Used and Similarly for Copy Constructor

There are some situations where a move constructor shouldn't be used. For example, if the object being moved is a constant object, or if the object being moved has a small amount of data that can be copied quickly, then a move constructor is unnecessary and may even be slower than a copy constructor.

Similarly, there are some situations where a copy constructor can't be used. For example, if the object being copied has resources that can't be copied, such as a file handle or a network connection, then a copy constructor may not be possible.

In general, it's important to consider the resources being used by an object, and the performance implications of copying or moving those resources, in order to decide whether to use a move constructor, a copy constructor, or some other approach.

## NRVO\RVO
NRVO (Named Return Value Optimization) and RVO (Return Value Optimization) are two techniques used by C++ compilers to optimize the return of values from functions.

RVO is a compiler optimization technique that allows a function to return a value by constructing it directly into the memory location where it will be stored by the caller, without needing to create a temporary object and then copy or move it to the caller's location. This can significantly improve performance by reducing the number of object copies or moves that need to be performed.

NRVO is a specific optimization of RVO where the object being returned is a named object (i.e., it has a name in the function) that can be constructed directly into the caller's location without the need for any additional copying or moving. In other words, the object is constructed in place at the location where it will be used by the caller.


# Optimisation time: move defeats copy

Lets move on some examples
## No references, move semantics and NRVO\RVO
![Level 0](https://github.com/deGekata/IntSpector/blob/bc2f6f918ac79cf4d514f6db294bfbf23f3a1d7c/lab_data/NoOptMoveRef.png)
Here we can see `COPY_COUNT=8`, `MOVE_COUNT=0`. Now we want decrease count of copies. First step will be references: passing arguments by references helps you to avoid copies and work with objects directly 

## No move semantics and NRVO\RVO, has references
![Level 1](https://github.com/deGekata/IntSpector/blob/bc2f6f918ac79cf4d514f6db294bfbf23f3a1d7c/lab_data/NoOptMove_HasRef.png)
Now `COPY_COUNT=5`, `MOVE_COUNT=0`. Pretty good result, we passed arguments by references and there are 3 copies less, thats simple. Lets get out our special weapon: move semantics. 
## No NRVO\RVO, has references and move semantics
![Level 2](https://github.com/deGekata/IntSpector/blob/bc2f6f918ac79cf4d514f6db294bfbf23f3a1d7c/lab_data/NoOpt_HasRefMove.png)
Now there are no copies left, they all have shifted to moves:`MOVE_COUNT=5`. Our last frontier: great power of compiler: `NRVO\RVO` Now it locate returned object right in place, where it will be used by caller 

## Has references, move semantics and NRVO\RVO
![Level 3](https://github.com/deGekata/IntSpector/blob/bc2f6f918ac79cf4d514f6db294bfbf23f3a1d7c/lab_data/HasRefMoveOpt.png)

Thats all for now, my brothers. My greetings! We have come a long way from ` COPY_COUNT=8,MOVE_COUNT=0 -> COPY_COUNT=5,MOVE_COUNT=0 -> COPY_COUNT=0,MOVE_COUNT=5 -> COPY_COUNT=0,MOVE_COUNT=2`