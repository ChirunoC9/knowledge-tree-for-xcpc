#include <bits/stdc++.h>

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 2e5 + 10;
struct Info {
    int val;
    Info(int val = inf<int>) : val(val) {}
    Info operator + (const Info &o) const {
        return Info{std::max(this->val, o.val)};
    }
};