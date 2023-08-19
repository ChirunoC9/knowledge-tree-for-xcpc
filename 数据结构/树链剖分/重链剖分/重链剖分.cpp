#include <bits/stdc++.h>

void Main() {
    int n;
    std::cin >> n;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        std::cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<int> dfn(n, -1), rnk(n, -1), siz(n, -1), son(n, -1), dep(n, -1), top(n, -1), fa(n, -1);
    auto Build = [&](int root) -> void {
        auto dfs1 = [&](auto &&dfs, int from) -> void {
            siz[from] = 1;
            son[from] = -1;
            for (auto to : adj[from]) {
                if (dep[to] == -1) {
                    dep[to] = dep[from] + 1;
                    fa[to] = from;
                    dfs(dfs, to);
                    siz[from] += siz[to];
                    if (son[from] == -1 || siz[to] > son[from])
                        son[from] = to;
                }
            }
        };
        auto dfs2 = [&, stamp{-1}](auto &&dfs, int from, int root) mutable -> void {
            top[from] = root;
            dfn[from] = ++ stamp;
            rnk[stamp] = from;
            if (son[from] == -1)
                return;
            dfs(dfs, son[from], root);
            for (auto to : adj[from])
                if (to != fa[from] && to != son[from])
                    dfs(dfs, to, to);
        };
        dep[root] = 0;
        dfs1(dfs1, root);
        dfs2(dfs2, root, root);
    };
    Build(1);
}