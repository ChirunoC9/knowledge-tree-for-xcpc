#include <bits/stdc++.h>

// clang-format off

constexpr int MAX_N = 2e1 + 10;

struct Info {

    friend Info operator + (const Info &a, const Info &b) {

    }
};
struct Node {
    Info val;
} seg[MAX_N * 4];

__attribute__ ((__always_inline__))
void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id, const auto &seq) {
    if (l == r) {

    } else {
        auto mid = l + (r - l) / 2;
        build(l, mid, id * 2, seq);
        build(mid + 1, r, id * 2 + 1, seq);
        rise(id);
    }
}

void apply(int l, int r, int id, int target, const Info &d) {
    if (l == r) {
        
    } else {
        auto mid = l + (r - l) / 2;
        if (target <= mid) {
            apply(l, mid, id * 2, target, d);
        } else {
            apply(mid + 1, r, id * 2 + 1, target, d);
        }
        rise(id);
    }
}

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + (r - l) / 2;
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 + 1, ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid)
                   + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}
// clang-format on
