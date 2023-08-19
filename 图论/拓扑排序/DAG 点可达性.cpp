#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    
    std::vector adj(n, std::vector<int>{});
    std::vector<int> indegree(n);
    for (int i = 0; i < m; i ++) {
        int from, to;
        std::cin >> from >> to;
        from --; to --;
        adj[to].emplace_back(from);
        indegree[from] ++;
    }
    
    std::vector<std::bitset<2000>> able(n);
    std::queue<int> q;
    for (int i = 0; i < n; i ++) {
        able[i][i] = 1;
        if (indegree[i] == 0) {
            q.emplace(i);
        }
    }
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (auto to : adj[from]) {
            able[to] |= able[from];
            if (-- indegree[to] == 0) {
                q.emplace(to);
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (able[i][j]) {
                std::cout << j << ' ';
            }
        }
        std::cout << '\n';
    }
}