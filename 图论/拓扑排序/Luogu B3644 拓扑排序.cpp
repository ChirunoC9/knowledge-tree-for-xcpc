#include <bits/stdc++.h>

void Main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector adj(n, std::vector<int>{});
    std::vector<int> ind(n);
    for (int i = 0; i < n; i ++) {
        while (true) {
            int x;
            std::cin >> x;
            x --;
            if (x == -1) {
                break;
            }
            adj[i].emplace_back(x);
            ind[x] ++;
        }
    }

    std::vector<int> ret;
    ret.reserve(n);
    for (int i = 0; i < n; i ++) {
        if (ind[i] == 0) {
            ret.emplace_back(i);
        }
    }
    for (int i = 0; i < ret.size() && i < n; i ++) {
        int from = ret[i];
        for (auto to : adj[from]) {
            if (-- ind[to] == 0) {
                ret.emplace_back(to);
            }
        }
    }

    assert(ret.size() == n);
    for (auto x : ret) 
        std::cout << x + 1 << ' ';
    std::cout << '\n';
}
