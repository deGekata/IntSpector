namespace MyStd {
    template <class T>
    struct RemoveReference {
        typedef T type;
    };

    template <class T>
    struct RemoveReference<T&> {
        typedef T type;
    };

    template <class T>
    struct RemoveReference<T&&> {
        typedef T type;
    };

    template <class T>
    constexpr typename RemoveReference<T>::type&&
    move(T&& object) {
        return static_cast<typename RemoveReference<T>::type&&>(object);
    }

    template <class T>
    constexpr T&&
    forward(typename RemoveReference<T>::type& object) {
        return static_cast<T&&>(object);
    }

    template <class T>
    constexpr T&&
    forward(typename RemoveReference<T>::type&& object) {
        return static_cast<T&&>(object);
    }
}