#include <bits/stdc++.h>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<std::pair<int, int>>{});
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        adj[u].emplace_back(v, w);
    }

    std::vector<int> dis(n, inf<int>);
    std::vector<bool> inque(n);
    std::vector<int> cnt(n);
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        dis[i] = 0;
        inque[i] = true;
        q.emplace(i);
    }

    bool have_loop = false;
    while (!q.empty() && !have_loop) {
        int from = q.front();
        q.pop();
        inque[from] = false;
        for (auto [to, w] : adj[from]) {
            if (dis[to] > dis[from] + w) {
                dis[to] = dis[from] + w;
                cnt[to] = cnt[from] + w;
                if (cnt[to] > n - 1) {
                    have_loop = true;
                    break;
                }
                if (!inque[to]) {
                    inque[to] = true;
                    q.emplace(to);
                }
            }
        }
    }

    if (have_loop) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}