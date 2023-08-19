#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n + 1, std::vector<std::pair<int,int>>());
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    std::vector<int> dfn(n + 1, -1), low(n + 1);
    std::vector<bool> is_bridge(m + 1);
    auto tarjan = [&, stamp{0}](auto &&dfs, int from, int eid) mutable -> void {
        dfn[from] = low[from] = ++ stamp;
        for (auto [to, neid] : adj[from]) {
            if (dfn[to] == -1) {
                dfs(dfs, to, neid);
                low[from] = std::min(low[from], low[to]);
            } else if (neid != eid) {
                low[from] = std::min(low[from], dfn[to]);
            }
        }
        if (dfn[from] == low[from] && eid != -1) {
            is_bridge[eid] = true;
        }
    };
    
    for (int i = 1; i <= n; i ++) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i, -1);
        }
    }

    std::vector<bool> vis(n + 1);
    auto dfs = [&](auto &&dfs, int from, std::vector<int> &ls) -> void {
        ls.emplace_back(from);
        vis[from] = true;
        for (auto [to, neid] : adj[from]) {
            if (!is_bridge[neid] && !vis[to]) {
                dfs(dfs, to, ls);
            }
        }
    };
    std::vector<std::vector<int>> dcc;
    dcc.reserve(n);
    for (int i = 1; i <= n; i ++) {
        if (!vis[i]) {
            dcc.emplace_back(std::vector<int>{});
            dfs(dfs, i, dcc.back());
        }
    }

    std::cout << dcc.size() << '\n';
    for (auto &vec : dcc) {
        std::cout << vec.size() << ' ';
        for (auto v : vec) {
            std::cout << v << ' ';
        }
        std::cout << '\n';
    }
}