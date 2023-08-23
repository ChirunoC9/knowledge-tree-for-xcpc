// LUOGU_RID: 110120255
#include <bits/stdc++.h>
// #ifndef ONLINE_JUDGE
//     #include ".vscode/debug.hpp"
// #else
//     #define debug(...)
// #endif

template <typename T, typename Compare = std::greater<T>, template <typename E, typename Alloc = std::allocator<E>> typename Container = std::vector>
using PriorityQueue = std::priority_queue<T, Container<T>, Compare>;
template <typename T, template <typename E, typename Alloc = std::allocator<E>> typename Container = std::vector>
using Stack = std::stack<T, Container<T>>;
using i64 = int64_t;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

struct Macro {};
template <> struct std::ranges::view_interface<Macro> {
    static void Main();
};

using namespace std;

template <typename T>
struct BaseChthollyTree {
    int L, R;
    std::map<int,T> mp;  // 区间开始 : 数据

    // [l, r)
    BaseChthollyTree(int l, int r, const T &init_val)
        : L(l), R(r), mp{ {l - 1, init_val}, {r, init_val} } {
    }

    void Split(int x) {
        auto it = std::prev(mp.upper_bound(x));
        mp[x] = it->second;
    }

    // 删除 [l, r - 1], 建立新区间
    void Assign(int l, int r, const T &v) {
        Split(l); Split(r);
        auto it = mp.find(l);
        while (it->first != r) {
            it = mp.erase(it);
        }
        mp[l] = v;
    }

    // 其他操作
    // void Opt() {}
};

struct ChthollyTree : BaseChthollyTree<i64> {
    ChthollyTree(int l, int r, const i64 &init_val) : BaseChthollyTree<i64>(l, r, init_val) {}

    void Add(int l, int r, i64 k) {
        Split(l); Split(r);
        for (auto it = mp.find(l); it->first < r; it = std::next(it)) {
            it->second += k;
        }
    }

    i64 GetRankFromMin(int l, int r, int kth) {
        Split(l); Split(r);
        
        std::vector<std::pair<i64,int>> v;
        for (auto it = mp.find(l); it->first < r; it = std::next(it)) {
            v.emplace_back(it->second, next(it)->first - it->first);
        }
        std::ranges::sort(v, [](const auto &a, const auto &b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second < b.second;
        });
        
        for (auto [val, cnt] : v) {
            kth -= cnt;
            if (kth <= 0) {
                return val;
            }
        }
        return -1;
    }

    i64 GetSum(int l, int r, i64 k, i64 p) {
        auto Pow = [&](i64 x, i64 i) -> i64 {
            i64 ret = 1 % p;
            x %= p;
            for (; i > 0; i >>= 1, (x *= x) %= p) {
                if (i & 1) {
                    (ret *= x) %= p;
                }
            }
            return ret;
        };

        Split(l); Split(r);
        i64 ret = 0;
        for (auto it = mp.find(l); it->first < r; it = std::next(it)) {
            int l = it->first, r = std::next(it)->first;
            i64 val = it->second;
            (ret += Pow(val, k) * (r - l) % p) %= p;
        }
        return ret;
    }
};

auto std::ranges::view_interface<Macro>::Main() -> void {
    int n, q;
    cin >> n >> q;

    i64 seed, vmax;
    cin >> seed >> vmax;

    auto GetRnd = [&]() {
        i64 ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };

    ChthollyTree odt(1, n + 1, i64(0));
    for (int i = 1; i <= n; i ++) {
        odt.mp[i] = (GetRnd() % vmax) + 1;
    }

    for (int _ = 1; _ <= q; _ ++) {
        int opt, l, r;
        i64 x, y;

        opt = GetRnd() % 4 + 1;
        l = GetRnd() % n + 1;
        r = GetRnd() % n + 1;

        if (l > r) {
            swap(l, r);
        }

        if (opt == 3) {
            x = (GetRnd() % (r - l + 1)) + 1;
        } else {
            x = (GetRnd() % vmax) + 1;
        }
        if (opt == 4) {
            y = (GetRnd() % vmax) + 1;
        }

        if (opt == 1) {
            odt.Add(l, r + 1, x);
        } else if (opt == 2) {
            odt.Assign(l, r + 1, x);
        } else if (opt == 3) {
            cout << odt.GetRankFromMin(l, r + 1, x) << '\n';
        } else {
            cout << odt.GetSum(l, r + 1, x, y) << '\n';
        }
    }
}

auto main() -> int32_t {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(15);

    int test = 1;
    // std::cin >> test;

    for (int rp = 1; test --> 0; rp ++) {
        std::ranges::view_interface<Macro>::Main();
    }
}