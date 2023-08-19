#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        std::cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<int> dep(n, -1);
    auto dfs = [&](auto &&dfs, int from, int come) -> void {
        for (auto to : adj[from]) {
            if (to != come) {
                dep[to] = dep[from] + 1;
                dfs(dfs, to, from);
            }
        }
    };
    
    dep[0] = 1;
    dfs(dfs, 0, -1);
    
    int nex = std::ranges::max_element(dep) - dep.begin();
    dep[nex] = 0;
    dfs(dfs, nex, -1);

    std::cout << std::ranges::max(dep) << '\n';
}