#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n + 1, std::vector<int>());
    for (int i = 1; i <= m; i ++) {
        int u, v;
        std::cin >> u >> v;
        if (u == v)
            continue;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<int> dfn(n + 1, -1), low(n + 1, -1), stk;
    std::vector<bool> is_cut(n + 1);
    std::vector<std::vector<int>> v_dcc, belong_v_dcc(n + 1);
    v_dcc.reserve(n);
    
    auto tarjan = [&, stamp{0}](auto &&dfs, int from, bool is_root) mutable -> void {
        dfn[from] = low[from] = ++ stamp;
        if (adj[from].empty() && is_root) {
            v_dcc.push_back({from});
            belong_v_dcc[from].emplace_back(int(v_dcc.size()) - 1);
            return;
        }
        stk.emplace_back(from);

        int cnt = 0;
        for (auto to : adj[from]) {
            if (dfn[to] == -1) {
                dfs(dfs, to, false);
                low[from] = std::min(low[from], low[to]);
                
                if (low[to] >= dfn[from]) {
                    cnt ++;
                    if (!is_root || cnt >= 2) {
                        is_cut[from] = true;
                    }
                
                    int now = 0;
                    v_dcc.push_back({});
                    auto &new_dcc = v_dcc.back();
                    int dcc_id = int(v_dcc.size()) - 1;
                    do {
                        now = stk.back();
                        stk.pop_back();
                        new_dcc.emplace_back(now);
                        belong_v_dcc[now].emplace_back(dcc_id);
                    } while (now != to);
                    new_dcc.emplace_back(from);
                    belong_v_dcc[from].emplace_back(dcc_id);
                }

            } else {
                low[from] = std::min(low[from], dfn[to]);
            }
        }
    };
    for (int i = 1; i <= n; i ++) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i, true);
        }
    }

    std::cout << v_dcc.size() << '\n';
    for (auto &v_dcc : v_dcc) {
        std::cout << v_dcc.size() << ' ';
        for (auto &x : v_dcc) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
}