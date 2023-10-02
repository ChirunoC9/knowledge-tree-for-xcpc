#include <bits/stdc++.h>

template <std::integral _Ty>
struct Fraction {
public:
    using value_type = _Ty;

public:
    _Ty numerator, denominator;

public:
    constexpr explicit Fraction() noexcept : numerator(0), denominator(1) {}

    constexpr explicit Fraction(_Ty numerator, _Ty denominator) noexcept
        : numerator(numerator), denominator(denominator) {
        assert(denominator != 0);
        Reduce();
    }

    constexpr Fraction(_Ty numerator) noexcept : numerator(numerator), denominator(1) {}

    constexpr auto Reduce() noexcept -> void {
        auto gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    constexpr auto operator+(const Fraction &other) const noexcept -> Fraction {
        auto result =
            Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
        result.Reduce();
        return result;
    }

    constexpr auto operator+=(const Fraction &other) noexcept -> Fraction & {
        *this = *this + other;
        return *this;
    }

    constexpr auto operator-(const Fraction &other) const noexcept -> Fraction {
        auto result =
            Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
        result.Reduce();
        return result;
    }

    constexpr auto operator-=(const Fraction &other) noexcept -> Fraction & {
        *this = *this + other;
        return *this;
    }

    constexpr auto operator*(const Fraction &other) const noexcept -> Fraction {
        auto result = Fraction(numerator * other.numerator, denominator * other.denominator);
        result.Reduce();
        return result;
    }

    constexpr auto operator*=(const Fraction &other) noexcept -> Fraction & {
        numerator *= other.numerator;
        denominator *= other.denominator;
        Reduce();
        return *this;
    }

    constexpr auto operator/(const Fraction &other) noexcept -> Fraction {
        auto result = Fraction(numerator * other.denominator, denominator * other.numerator);
        result.Reduce();
        return result;
    }

    constexpr auto operator/=(const Fraction &other) noexcept -> Fraction & {
        numerator *= other.denominator;
        denominator *= other.numerator;
        Reduce();
        return *this;
    }

    constexpr auto Pow(std::integral auto i) const noexcept -> Fraction {
        Fraction result = _MakeNoReduceFraction(1, 1), a = _MakeNoReduceFraction(numerator, denominator);
        while (i > 0) {
            if (i & 1) {
                result *= a;
            }
            a *= a;
            i >>= 1;
        }
        return result;
    }

    constexpr auto operator^(std::integral auto i) const noexcept -> Fraction {
        return Pow(i);
    }

    constexpr auto operator^=(std::integral auto i) noexcept -> Fraction & {
        *this = Pow(i);
        return *this;
    }

    friend constexpr auto operator+(const Fraction &a, const std::integral auto &b) noexcept -> Fraction {
        auto result = a;
        result.numerator += b * result.denominator;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator+(const std::integral auto &a, const Fraction &b) noexcept -> Fraction {
        auto result = b;
        result.numerator += a * result.denominator;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator-(const Fraction &a, const std::integral auto &b) noexcept -> Fraction {
        auto result = a;
        result.numerator -= b * result.denominator;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator-(const std::integral auto &a, const Fraction &b) noexcept -> Fraction {
        auto result = b;
        result.numerator -= a * result.denominator;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator*(const Fraction &a, const std::integral auto &b) noexcept -> Fraction {
        auto result = a;
        result.numerator *= b;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator*(const std::integral auto &a, const Fraction &b) noexcept -> Fraction {
        auto result = b;
        result.numerator *= a;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator/(const Fraction &a, const std::integral auto &b) noexcept -> Fraction {
        auto result = a;
        result.denominator *= b;
        result.Reduce();
        return result;
    }

    friend constexpr auto operator/(const std::integral auto &a, const Fraction &b) noexcept -> Fraction {
        auto result = b;
        result.denominator *= a;
        result.Reduce();
        return result;
    }

    friend auto operator>>(std::istream &in, Fraction &x) -> std::istream & {
        _Ty a, b;
        in >> a >> b;
        x = Fraction(a, b);
        return in;
    }

    friend auto operator<<(std::ostream &out, const Fraction &x) -> std::ostream & {
        out << x.numerator << '/' << x.denominator;
        return out;
    }

private:
    inline static constexpr auto _MakeNoReduceFraction(_Ty numerator, _Ty denominator) noexcept {
        Fraction result;
        result.numerator = numerator;
        result.denominator = denominator;
        return result;
    }
};
