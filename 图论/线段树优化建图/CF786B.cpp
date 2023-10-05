/**
 * 有 n 个点的有向图，q 次操作，起点为 s ，每种操作为三种操作中的一种：
 * 1. u -> v 连有向边，边权为 w
 * 2. u -> [l, r] 的每个点连有向边，边权为 w
 * 3. [l, r] 的每个点 -> u 连有向边，边权为 w
 * 求 s 到其他点的最短路径
 */

#include <bits/stdc++.h>

template <typename _Ty>
constexpr _Ty inf = std::numeric_limits<_Ty>::max() / 2;
using u8 = uint8_t;
using i64 = int64_t;

using namespace std;

const int N = 1e5 + 10;
int vpos[N];

// no shift := out
// shift := in
void build(int l, int r, int id, int SHIFT,
           vector<vector<pair<int, i64>>> &adj) {
    if (l == r) {
        vpos[l] = id;
        adj[id + SHIFT].emplace_back(id, 0);
        adj[id].emplace_back(id + SHIFT, 0);
    } else {
        auto mid = l + (r - l) / 2;
        build(l, mid, id * 2, SHIFT, adj);
        build(mid + 1, r, id * 2 + 1, SHIFT, adj);
        // out
        adj[id].emplace_back(id * 2, 0);
        adj[id].emplace_back(id * 2 + 1, 0);
        // in
        adj[id * 2 + SHIFT].emplace_back(id + SHIFT, 0);
        adj[id * 2 + 1 + SHIFT].emplace_back(id + SHIFT, 0);
    }
}

// opt := 1 => in from -> out to
// opt := 2 => in v -> out [ml, mr]
// opt := 3 => in [ml, mr] -> out v
void apply(int l, int r, int id, int ml, int mr, int SHIFT,
           vector<vector<pair<int, i64>>> &adj, int v, int ew, int opt) {
    if (l == ml && r == mr) {
        if (opt == 2) {
            adj[vpos[v] + SHIFT].emplace_back(id, ew);
        } else {
            adj[id + SHIFT].emplace_back(vpos[v], ew);
        }
    } else {
        auto mid = l + (r - l) / 2;
        if (mr <= mid) {
            apply(l, mid, id * 2, ml, mr, SHIFT, adj, v, ew, opt);
        } else if (ml > mid) {
            apply(mid + 1, r, id * 2 + 1, ml, mr, SHIFT, adj, v, ew, opt);
        } else {
            apply(l, mid, id * 2, ml, mid, SHIFT, adj, v, ew, opt);
            apply(mid + 1, r, id * 2 + 1, mid + 1, mr, SHIFT, adj, v, ew, opt);
        }
    }
}

auto Main() -> void {
    int n, q, s;
    cin >> n >> q >> s;

    int SHIFT = n * 4;

    int N = n * 8 + 1;
    vector adj(N, vector<pair<int, i64>>{});
    build(1, n, 1, SHIFT, adj);

    for (int i = 0; i < q; i += 1) {
        int opt;
        cin >> opt;

        if (opt == 1) {
            int from, to, ew;
            cin >> from >> to >> ew;
            adj[vpos[from] + SHIFT].emplace_back(vpos[to], ew);
        } else {
            int v, l, r, ew;
            cin >> v >> l >> r >> ew;
            apply(1, n, 1, l, r, SHIFT, adj, v, ew, opt);
        }
    }

    priority_queue<pair<i64, int>,
                   vector<pair<i64, int>>,
                   greater<pair<i64, int>>>
        pq;
    vector<i64> dis(N, inf<i64>);
    vector<bool> vis(N);

    int sta = vpos[s];
    pq.emplace(dis[sta] = 0, sta);
    while (!pq.empty()) {
        int from = pq.top().second;
        pq.pop();
        if (vis[from])
            continue;
        vis[from] = true;
        for (auto [to, ew] : adj[from]) {
            if (!vis[to] && dis[to] > dis[from] + ew) {
                pq.emplace(dis[to] = dis[from] + ew, to);
            }
        }
    }

    for (int i = 1; i <= n; i += 1) {
        if (auto ret = dis[vpos[i]]; ret == inf<i64>) {
            cout << -1 << " \n"[i == n];
        } else {
            cout << ret << " \n"[i == n];
        }
    }
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(15);

    int test = 1;
    // std::cin >> test;

    for (int t = 0; t < test; t += 1) {
        Main();
    }
}