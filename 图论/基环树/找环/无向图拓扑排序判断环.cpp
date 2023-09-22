#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector adj(n, std::vector<int>{});
    std::vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++;
        deg[v]++;
    }

    std::vector<int> topu;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) {
            topu.emplace_back(i);
        }
    }
    for (int i = 0; i < topu.size() && i < n; i++) {
        int from = topu[i];
        for (auto to : adj[from]) {
            if (--deg[to] == 1) {
                topu.emplace_back(to);
            }
        }
    }

    // 这里也可以判断剩下度 >= 2 的点
    std::vector<bool> vis(n);
    for (auto x : topu) {
        vis[x] = true;
    }

    std::cout << n - topu.size() << '\n';
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            std::cout << i + 1 << ' ';
        }
    }
    std::cout << '\n';
}