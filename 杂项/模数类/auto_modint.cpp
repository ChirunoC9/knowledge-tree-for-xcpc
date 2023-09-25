#include <concepts>
#include <cstdint>

#include <iostream>

namespace Leazozi::Type {
    template <std::integral auto _P>
        requires(_P >= 1)
    struct ModInt {
    private:
        using u32 = uint32_t;
        using i32 = int32_t;
        using u64 = uint64_t;
        using i64 = int64_t;
        using i128 = __int128_t;
        using u128 = __uint128_t;

    public:
        using value_type = decltype(_P);

    private:
        value_type _value;

    public:
        inline static constexpr auto P = _P;

    public:
        constexpr ModInt() noexcept : _value(0) {}

        constexpr ModInt(std::integral auto value) noexcept {
            _value = value % P;
            if (_value < 0)
                _value += P;
        }

        explicit constexpr operator int() const noexcept {
            return _value;
        }

        explicit constexpr operator long long() const noexcept {
            return _value;
        }

        explicit constexpr operator bool() const noexcept {
            return _value > 0;
        }

        constexpr auto operator==(const ModInt &other) const noexcept -> bool {
            return _value == other._value;
        }

        constexpr auto operator!=(const ModInt &other) const noexcept -> bool {
            return _value != other._value;
        }

        constexpr auto operator-() const noexcept -> ModInt {
            return ModInt{_value ? P - _value : 0};
        }

        constexpr auto operator+() const noexcept -> ModInt {
            return *this;
        }

        constexpr auto operator++() noexcept -> ModInt & {
            ++_value;
            if (_value == P)
                _value = 0;
            return *this;
        }

        constexpr auto operator--() noexcept -> ModInt & {
            if (_value == 0)
                _value = P;
            --_value;
            return *this;
        }

        constexpr auto operator++(int) noexcept -> ModInt {
            auto prev = *this;
            ++*this;
            return prev;
        }

        constexpr auto operator--(int) noexcept -> ModInt {
            auto prev = *this;
            --*this;
            return prev;
        }

        constexpr auto operator+=(const ModInt &other) noexcept -> ModInt & {
            _value += other._value;
            if (_value >= P)
                _value -= P;
            return *this;
        }

        constexpr auto operator+(const ModInt &other) const noexcept -> ModInt {
            auto result = *this;
            result += other;
            return result;
        }

        constexpr auto operator-=(const ModInt &other) noexcept -> ModInt & {
            _value -= other._value;
            if (_value < 0)
                _value += P;
            return *this;
        }

        constexpr auto operator-(const ModInt &other) const noexcept -> ModInt {
            auto result = *this;
            result -= other;
            return result;
        }

        constexpr auto operator*=(const ModInt &other) noexcept -> ModInt & {
            if constexpr (std::is_same_v<value_type, i32> || std::is_same_v<value_type, int> ||
                          std::is_same_v<value_type, u32>) {
                _value = (value_type)(((u64)_value * other._value) % P);
            } else {
                _value = (value_type)((u128)_value * other._value) % P;
            }
            return *this;
        }

        constexpr auto operator*(const ModInt &other) const noexcept -> ModInt {
            auto result = *this;
            result *= other;
            return result;
        }

        constexpr auto operator^(std::integral auto i) const noexcept -> ModInt {
            return _Pow(*this, i);
        }

        constexpr auto operator^=(std::integral auto i) const noexcept -> ModInt & {
            *this = (*this) ^ i;
            return *this;
        }

        constexpr auto operator/=(const ModInt &other) noexcept -> ModInt & {
            return (*this) *= other.GetInv();
        }

        constexpr auto operator/(const ModInt &other) const noexcept -> ModInt {
            auto result = *this;
            result /= other;
            return result;
        }

        constexpr auto GetInv() const noexcept -> ModInt {
            return (*this) ^ (P - 2);
        }

        constexpr auto GetValue() const noexcept -> value_type {
            return _value;
        }

        friend constexpr auto operator+(const ModInt &a, const std::integral auto &b) noexcept -> ModInt {
            return a + ModInt(b);
        }

        friend constexpr auto operator+(const std::integral auto &a, const ModInt &b) noexcept -> ModInt {
            return ModInt(a) + b;
        }

        friend constexpr auto operator-(const ModInt &a, const std::integral auto &b) noexcept -> ModInt {
            return a - ModInt(b);
        }

        friend constexpr auto operator-(const std::integral auto &a, const ModInt &b) noexcept -> ModInt {
            return ModInt(a) - b;
        }

        friend constexpr auto operator*(const ModInt &a, const std::integral auto &b) noexcept -> ModInt {
            return a * ModInt(b);
        }

        friend constexpr auto operator*(const std::integral auto &a, const ModInt b) noexcept -> ModInt {
            return ModInt(a) * b;
        }

        friend constexpr auto operator/(const ModInt &a, const std::integral auto &b) noexcept -> ModInt {
            return a * ModInt(b).GetInv();
        }

        friend constexpr auto operator/(const std::integral auto &a, const ModInt &b) noexcept -> ModInt {
            return ModInt(a) * b.GetInv();
        }

        constexpr auto operator~() const noexcept -> ModInt {
            return GetInv();
        }

        friend auto operator>>(std::istream &in, ModInt &x) -> std::istream & {
            value_type d;
            in >> d;
            x = ModInt(d);
            return in;
        }

        friend auto operator<<(std::ostream &out, const ModInt &x) -> std::ostream & {
            out << x._value;
            return out;
        }

    private:
        inline static constexpr auto _Pow(ModInt a, std::integral auto i) noexcept -> ModInt {
            ModInt result = 1;
            while (i > 0) {
                if (i & 1) {
                    result *= a;
                }
                a *= a;
                i >>= 1;
            }
            return result;
        }
    };
} // namespace Leazozi::Type