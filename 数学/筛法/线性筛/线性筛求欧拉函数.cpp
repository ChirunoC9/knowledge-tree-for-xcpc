#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e7 + 10;

int phi[N];
std::bitset<N> npr;
std::vector<int> pri;

void Init() {
    npr[0] = npr[1] = 1;
    phi[1] = 1;

    for (int i = 2; i < N; i++) {
        if (!npr[i]) {
            pri.emplace_back(i);
            phi[i] = i - 1;
        }

        for (i64 j : pri) {
            if (i * j >= N)
                break;
            npr[i * j] = 1;
            if (i % j == 0) {
                phi[i * j] = phi[i] * j;
                break;
            } else {
                phi[i * j] = phi[i] * (j - 1);
            }
        }
    }
}