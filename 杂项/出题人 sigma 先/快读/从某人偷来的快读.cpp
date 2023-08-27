#include <bits/stdc++.h>

class Scanner {
public:
    explicit Scanner(std::FILE *f = stdin,
                     std::size_t enough_buffer_size = 1 << 25)
        : __file(f), __buffer(new char[enough_buffer_size + 32]),
          __buffer_head(__buffer),
          __buffer_tail(__buffer + std::fread(__buffer, sizeof(char),
                                              enough_buffer_size + 32,
                                              __file)) {
        *__buffer_tail = '\0';
    }
    ~Scanner() { delete[] __buffer; }

    template <typename __ty>
    std::enable_if_t<std::is_integral_v<__ty> && !std::is_same_v<__ty, char> &&
                         std::is_signed_v<__ty>,
                     bool>
    read(__ty &__n) {
        __n = 0;
        while (*__buffer_head != '-' && std::isspace(*__buffer_head))
            ++__buffer_head;
        bool __is_neg = *__buffer_head == '-' && ++__buffer_head;
        auto __old_buffer_head = __buffer_head;
        if (__is_neg)
            while (std::isdigit(*__buffer_head))
                __n = __n * 10 - __ty(*__buffer_head++ - '0');
        else
            while (std::isdigit(*__buffer_head))
                __n = __n * 10 + __ty(*__buffer_head++ - '0');
        return __buffer_head != __old_buffer_head;
    }

    template <typename __ty>
    std::enable_if_t<std::is_integral_v<__ty> && !std::is_same_v<__ty, char> &&
                         std::is_unsigned_v<__ty>,
                     bool>
    read(__ty &__n) {
        __n = 0;
        while (*__buffer_head != '-' && std::isspace(*__buffer_head))
            ++__buffer_head;
        auto __old_buffer_head = __buffer_head;
        while (std::isdigit(*__buffer_head))
            __n = __n * 10 + __ty(*__buffer_head++ - '0');
        return __buffer_head != __old_buffer_head;
    }

    template <typename... __type_list> bool read(__type_list &...__n_list) {
        return (... && this->read(__n_list));
    }

private:
    std::FILE *__file;
    char *__buffer, *__buffer_head, *__buffer_tail;
};