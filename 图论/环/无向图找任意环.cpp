#include <cstdint>

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using u8 = uint8_t;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<std::pair<int, int>>{});
    for (int i = 0; i < m; i += 1) {
        int from, to;
        std::cin >> from >> to;
        adj[from].emplace_back(to, i);
        adj[to].emplace_back(from, i);
    }

    std::vector<u8> vis(n);
    std::vector<std::pair<int, int>> stk;
    std::vector<int> edge_list, vertex_list;
    stk.reserve(n);
    edge_list.reserve(m);
    vertex_list.reserve(n);

    auto dfs = [&](auto &dfs, int from, int come_eid) -> bool {
        vis[from] = 1;
        stk.emplace_back(from, come_eid);
        for (auto [to, next_eid] : adj[from]) {
            if (next_eid == come_eid) {
                continue;
            }
            if (vis[to] == 0) {
                if (dfs(dfs, to, next_eid)) {
                    return true;
                }
            } else if (vis[to] == 1) {
                edge_list.emplace_back(next_eid);
                while (stk.back().first != to) {
                    vertex_list.emplace_back(stk.back().first);
                    edge_list.emplace_back(stk.back().second);
                    stk.pop_back();
                }
                vertex_list.emplace_back(to);
                std::ranges::reverse(edge_list);
                std::ranges::reverse(vertex_list);
                return true;
            }
        }
        vis[from] = 2;
        stk.pop_back();
        return false;
    };

    for (int i = 0; i < n; i += 1) {
        if (!vis[i] && dfs(dfs, i, -1)) {
            break;
        }
    }

    if (edge_list.empty()) {
        std::cout << -1 << '\n';
    } else {
        std::cout << edge_list.size() << '\n';
        for (auto x : vertex_list) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        for (auto x : edge_list) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
}