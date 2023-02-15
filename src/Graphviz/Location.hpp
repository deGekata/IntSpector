#ifndef LOCATION_HPP
#define LOCATION_HPP


template <typename T, size_t S>
inline constexpr size_t get_file_name_offset(const T (& str)[S], size_t i = S - 1)
{
    return (str[i] == '/' || str[i] == '\\') ? i + 1 : (i > 0 ? get_file_name_offset(str, i - 1) : 0);
}

template <typename T>
inline constexpr size_t get_file_name_offset(T (& str)[1])
{
    return 0;
}

#define __LOCATION__ { &__FILE__[get_file_name_offset(__FILE__)], __LINE__, __FUNCTION__}
struct Location_t {
    const char* file = nullptr;
    int line = 0;
    const char* func = nullptr;
};

#endif // LOCATION_HPP