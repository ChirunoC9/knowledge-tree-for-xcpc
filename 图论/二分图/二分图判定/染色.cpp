#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<int> col(n, -1);
    auto dfs = [&](auto &&dfs, int from) -> bool {
        for (auto to : adj[from]) {
            if (col[to] == -1) {
                col[to] = col[from] ^ 1;
                dfs(dfs, to);
            } else if (col[to] == col[from]) {
                return false;
            }
        }
        return true;
    };
    
    bool ok = true;
    for (int i = 0; i < n && ok; i ++) {
        if (col[i] == -1) {
            col[i] = 0;
            ok &= dfs(dfs, i);
        }
    }

    if (ok) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}