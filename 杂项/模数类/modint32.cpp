#include "bits/stdc++.h"

template <int _P>
struct ModInt32 {
private:
    using i32 = int32_t;
    using i64 = int64_t;

private:
    int _value;
    inline static constexpr int P = _P;

public:
    inline static constexpr int ModValue = _P;

public:
    constexpr ModInt32() noexcept : _value(0) {}

    constexpr ModInt32(i64 __value) noexcept {
        _value = __value % P;
        if (_value < 0)
            _value += P;
    }

    constexpr explicit operator int() const noexcept {
        return _value;
    }

    constexpr explicit operator long long() const noexcept {
        return _value;
    }

    constexpr explicit operator bool() const noexcept {
        return _value > 0;
    }

    constexpr bool operator==(const ModInt32 &other) const noexcept {
        return _value == other._value;
    }

    constexpr bool operator!=(const ModInt32 &other) const noexcept {
        return _value != other._value;
    }

    constexpr ModInt32 operator-() const noexcept {
        return ModInt32(_value ? P - _value : 0);
    }

    constexpr ModInt32 operator+() const noexcept {
        return *this;
    }

    constexpr ModInt32 &operator++() noexcept {
        ++_value;
        if (_value == P)
            _value = 0;
        return *this;
    }

    constexpr ModInt32 &operator--() noexcept {
        if (_value == 0)
            _value = P;
        --_value;
        return *this;
    }

    constexpr ModInt32 operator++(int) noexcept {
        auto prev = *this;
        ++*this;
        return prev;
    }

    constexpr ModInt32 operator--(int) noexcept {
        auto prev = *this;
        --*this;
        return prev;
    }

    constexpr ModInt32 &operator+=(const ModInt32 &o) noexcept {
        _value += o.v;
        if (_value >= P)
            _value -= P;
        return *this;
    }
    constexpr ModInt32 operator+(const ModInt32 &o) const noexcept {
        return ModInt32(*this) += o;
    }
};