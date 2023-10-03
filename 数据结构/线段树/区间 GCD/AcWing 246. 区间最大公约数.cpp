#include "bits/stdc++.h"

using i64 = int64_t;

const int N = 500000 + 10;
struct Info {
    i64 sum, gcd;
    Info(i64 sum = 0, i64 gcd = 0) : sum(sum), gcd(gcd) {

    }
    Info operator + (const Info &o) const {
        return Info {
            sum + o.sum,
            std::gcd(gcd, o.gcd)
        };
    }
};
struct Node {
    Info val;
} seg[N * 4];

void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

template <typename T>
void build(int l, int r, int id, const T &a) {
    if (l == r) {
        seg[id].val = {a[l], a[l]};
    } else {
        auto mid = l + ((r - l) >> 1);
        build(l, mid, id * 2, a);
        build(mid + 1, r, id * 2 + 1, a);
        rise(id);
    }
}

void change(int l, int r, int id, int tag, i64 d) {
    if (l == r) {
        seg[id].val.sum += d;
        seg[id].val.gcd += d;
    } else {
        auto mid = l + ((r - l) >> 1);
        if (tag <= mid) {
            change(l, mid, id * 2, tag, d); 
        } else {
            change(mid + 1, r, id * 2 + 1, tag, d);
        }
        rise(id);
    }
}

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        int mid = l + ((r - l) >> 1);
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 + 1, ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, q;
    std::cin >> n >> q;

    std::vector<i64> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i ++) {
        b[i] = a[i] - a[i - 1];
    }

    build(1, n, 1, b);
    
    while (q --) {
        char opt;
        std::cin >> opt;

        if (opt == 'Q') {
            int l, r;
            std::cin >> l >> r;

            if (l == r) {
                std::cout << query(1, n, 1, 1, l).sum << '\n';
            } else {
                std::cout << std::gcd(query(1, n, 1, 1, l).sum, query(1, n, 1, l + 1, r).gcd) << '\n';
            }
        } else {
            int l, r;
            std::cin >> l >> r;
            i64 d;
            std::cin >> d;

            change(1, n, 1, l, d);
            if (r + 1 <= n) {
                change(1, n, 1, r + 1, -d);
            }
        }
    }
}