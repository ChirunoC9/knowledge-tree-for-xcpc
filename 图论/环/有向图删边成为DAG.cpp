// 给定一张有向图
// 若起点为1
// 那么至少删去多少条边，使得从1到其他点的路径不构成环

#include <bits/stdc++.h>

using u8 = uint8_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<std::pair<int, int>>{});
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].emplace_back(v, i);
    }

    // 0 := 未遍历
    // 1 := 以 x 为根的子树仍然在遍历
    // 2 := 以 x 为根的子树遍历结束
    std::vector<u8> vis(n);
    std::vector<bool> del(n);
    auto dfs = [&, stamp{0}](auto &self, int from) -> void {
        vis[from] = 1;
        for (auto [to, neid] : adj[from]) {
            if (!vis[to]) {
                self(self, to);
                continue;
            }
            // 遍历到一个其子树仍未遍历完毕的节点，则该边为返祖边
            if (vis[to] == 1) {
                del[neid] = true;
            }
        }
        vis[from] = 2;
    };
    dfs(dfs, 0);

    std::cout << std::count(vis.begin(), vis.end(), true) << '\n';
    for (int i = 0; i < m; i++) {
        if (del[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
}