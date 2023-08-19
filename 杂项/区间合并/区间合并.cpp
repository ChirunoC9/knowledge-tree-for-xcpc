#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int,int>> a(n);
    for (auto &[l, r] : a) {
        std::cin >> l >> r; // [l, r]
        l --;  // [l, r)
    }

    std::ranges::sort(a);
    std::vector ret{a.front()};
    for (auto &&[nl, nr] : a) {
        if (ret.back().second >= nl) {
            ret.back().second = std::max(ret.back().second, nr);
        } else {
            ret.emplace_back(nl, nr);
        }
    }

    std::cout << ret.size() << '\n';
    for (auto [l, r] : ret) {
        std::cout << l + 1 << ' ' << r << '\n';
    }
}