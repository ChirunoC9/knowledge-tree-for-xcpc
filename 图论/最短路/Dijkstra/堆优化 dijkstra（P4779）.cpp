#include <bits/stdc++.h>

template <typename Type>
constexpr Type inf = std::numeric_limits<Type>::max() / 2;
template <typename T, std::relation<T,T>
Compare = std::greater<T>> using Heap = std::priority_queue<T, std::vector<T>, Compare>;


int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m, s;
    std::cin >> n >> m >> s;
    s --;

    std::vector adj(n, std::vector<std::pair<int,int>>{});
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u --; v --;
        adj[u].emplace_back(v, w);
    }

    std::vector<int> dis(n, inf<int>);
    std::vector<bool> vis(n);
    Heap<std::pair<int,int>> heap;
    heap.emplace(dis[s] = 0, s);
    while (!heap.empty()) {
        int from = heap.top().second;
        heap.pop();
        if (vis[from]) continue;
        vis[from] = true;
        for (auto [to, ew] : adj[from]) {
            if (!vis[to] && dis[to] > dis[from] + ew) {
                heap.emplace(dis[to] = dis[from] + ew, to);
            }
        }
    }

    for (auto ret : dis) {
        std::cout << ret << ' ';
    }
    std::cout << '\n';
}