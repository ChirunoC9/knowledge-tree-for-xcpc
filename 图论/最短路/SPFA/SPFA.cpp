#include <bits/stdc++.h>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<std::pair<int,int>>{});
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u --; v --;
        adj[u].emplace_back(v, w);
    }

    int s, t;
    std::cin >> s >> t;

    std::queue<int> q;
    std::vector<int> dis(n, inf<int>);
    std::vector<int> cnt(n);
    std::vector<bool> vis(n);

    bool have_loop = false;

    q.emplace(s);
    dis[s] = 0;
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        vis[from] = false;
        for (auto [to, w] : adj[from]) {
            if (!vis[to] && dis[to] > dis[from] + w) {
                dis[to] = dis[from] + w;
                cnt[to] = cnt[from] + 1;
                if (cnt[to] > n - 1) {
                    have_loop = true;
                    break;
                }
                if (!vis[to]) {
                    q.emplace(to);
                    vis[to] = true;
                }
            }
        }
        if (have_loop) {
            break;
        }
    }

    if (have_loop) {
        std::cout << -1 << '\n';
    } else {
        std::cout << dis[t] << '\n';
    }
}