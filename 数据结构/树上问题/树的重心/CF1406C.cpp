#include <bits/stdc++.h>

void Main() {
    int n;
    std::cin >> n;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<int> vls;
    std::vector<int> siz(n), mx_siz(n);
    auto dfs = [&](auto &&dfs, int from, int come) -> void {
        siz[from] = 1;
        for (auto to : adj[from]) {
            if (to != come) {
                dfs(dfs, to, from);
                siz[from] += siz[to];
                mx_siz[from] = std::max(siz[to], mx_siz[from]);
            }
        }
        mx_siz[from] = std::max(mx_siz[from], n - siz[from]);
        if (mx_siz[from] <= n / 2) {
            vls.emplace_back(from);
        }
    };
    dfs(dfs, 0, -1);

    if (vls.size() == 1) {
        for (int i = 0; i < n; i ++) {
            for (int j : adj[i]) {
                std::cout << i + 1 << ' ' << j + 1 << '\n' << i + 1 << ' ' << j + 1 << '\n';
                return;
            }
        }
    } else {
        int x = vls[0], y = vls[1];
        for (auto z : adj[x]) {
            if (z != y) {
                std::cout << x + 1 << ' ' << z + 1 << '\n';
                std::cout << y + 1 << ' ' << z + 1 << '\n';
                return;
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int test;
    std::cin >> test;

    while (test --) {
        Main();
    }
}