#include <cmath>

#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    // a -> b => not a V b
    // 2 * u := not true; 2 * u + 1 := true
    std::vector adj(n * 2, std::vector<int>{});
    for (int i = 0; i < m; i += 1) {
        int u, uw, v, vw;
        std::cin >> u >> uw >> v >> vw;
        u -= 1;
        v -= 1;
        adj[u * 2 + !uw].emplace_back(v * 2 + vw);
        adj[v * 2 + !vw].emplace_back(u * 2 + uw);
    }

    std::vector<bool> vis(n * 2);
    std::vector<int> stk;

    // dfs 遍历图
    auto dfs = [&](auto &dfs, int from) -> bool {
        // 如果取反的另一个点已经被遍历过
        if (vis[from ^ 1]) {
            return false;
        } else if (vis[from]) {
            return true;
        }
        // 遍历路径标记
        vis[from] = true;
        stk.emplace_back(from);
        for (auto to : adj[from]) {
            if (!dfs(dfs, to)) {
                return false;
            }
        }
        return true;
    };
    // 2-SAT 工作
    auto two_sat = [&](int n) {
        // 遍历每个点
        for (int i = 0; i < n; i += 1) {
            if (vis[i * 2] || vis[i * 2 + 1]) {
                continue;
            }
            stk.clear();
            // 优先遍历 not true 点，以实现字典序最小
            if (!dfs(dfs, i * 2)) {
                // 如果不行，那么重新取消标记，并遍历另一个点
                while (!stk.empty()) {
                    vis[stk.back()] = false;
                    stk.pop_back();
                }
                if (!dfs(dfs, i * 2 + 1)) {
                    // 依然不行，说明无解
                    return false;
                }
            }
        }
        return true;
    };

    if (two_sat(n)) {
        std::cout << "POSSIBLE\n";
        for (int i = 0; i < n; i += 1) {
            if (vis[i * 2]) {
                std::cout << 0 << ' ';
            } else {
                std::cout << 1 << ' ';
            }
        }
        std::cout << '\n';
    } else {
        std::cout << "IMPOSSIBLE\n";
    }
}