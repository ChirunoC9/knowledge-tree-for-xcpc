#include <bits/stdc++.h>

template <std::integral T>
std::array<T, 3> exgcd(T a, T b) {
    if (b == 0) {
        return {a, 1, 0};
    } else {
        auto [g, x1, y1] = exgcd(b, a % b);
        return {g, y1, x1 - a / b * y1};
    }
}