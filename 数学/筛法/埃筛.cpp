#include <bits/stdc++.h>

template <std::size_t N>
std::pair<std::bitset<N>,std::vector<int>> GetPrimeList() {
    using i64 = int64_t;
    std::bitset<N> no_prime{};
    std::vector<int> prime;
    no_prime[0] = no_prime[1] = 1;
    for (int i = 2; i < no_prime.size(); i ++) {
        if (!no_prime[i]) {
            prime.emplace_back(i);
            for (i64 j = i * 2; j < no_prime.size(); j += i) {
                no_prime[j] = 1;
            }
        }
    }
    return std::pair{no_prime, prime};
}