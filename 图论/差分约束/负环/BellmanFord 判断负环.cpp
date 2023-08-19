#include <bits/stdc++.h>

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<std::pair<int,int>>{});
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u --, v --;
        adj[u].emplace_back(v, w);
    }

    std::vector<int> dis(n, inf<int>);
    auto bellman_ford = [&](int star) -> bool {
        std::fill(dis.begin(), dis.end(), inf<int>);
        dis[star] = 0;
        
        for (int i = 0; i < n; i ++) {
            bool flag = false;
            for (int from = 0; from < n; from ++) {
                if (dis[from] == inf<int>) continue;
                for (auto [to, w] : adj[from]) {
                    if (dis[to] > dis[from] + w) {
                        dis[to] = dis[from] + w;
                        flag = true;
                    }
                }
            }
            if (!flag) {
                return false;
            }
        }
        return true;
    };

    if (bellman_ford(0)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}