#include <bits/stdc++.h>

using i64 = int64_t;

const int N = 1e7 + 10;
std::bitset<N> no_prime;
std::vector<int> prime;

void init() {
    no_prime[0] = no_prime[1] = 1;
    for (int i = 2; i < no_prime.size(); i ++) {
        if (!no_prime[i])
            prime.emplace_back(i);
        for (i64 j : prime) {
            if (i * j >= no_prime.size()) 
                break;
            no_prime[i * j] = 1;
            if (i % j == 0)
                break;
        }
    }
}

template <std::size_t N>
std::pair<std::bitset<N>, std::vector<int>> GetPrimeList() {
    using i64 = int64_t;
    std::bitset<N> no_prime{};
    std::vector<int> prime;
    no_prime[0] = no_prime[1] = 1;
    for (int i = 2; i < no_prime.size(); i ++) {
        if (!no_prime[i])
            prime.emplace_back(i);
        for (i64 j : prime) {
            if (i * j >= no_prime.size()) 
                break;
            no_prime[i * j] = 1;
            if (i % j == 0)
                break;
        }
    }
    return std::pair{no_prime, prime};
}