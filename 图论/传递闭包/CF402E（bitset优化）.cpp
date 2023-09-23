#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    using Info = std::bitset<2000>;

    std::vector f(n, Info{});
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            std::cin >> w;
            if (w > 0) {
                f[i][j] = 1;
            }
        }
    }

    // Floyd 传递闭包
    // for (int k = 0; k < n; k++) {
    //     for (int i = 0; i < n; i++) {
    //         for (int j = 0; j < n; j++) {
    //             f[i][j] = f[i][j] | (f[i][k] & f[k][j]);
    //         }
    //     }
    // }

    // bitset 优化传递闭包
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i][k]) {
                f[i] |= f[k];
            }
        }
    }

    bool ok = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ok &= f[i][j];
        }
    }
    if (ok) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}