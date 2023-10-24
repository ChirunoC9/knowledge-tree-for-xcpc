#include <bits/stdc++.h>

// clang-format off
constexpr int MAX_N = 2e1 + 10;

struct Info {
    
    friend Info operator + (const Info &a, const Info &b) {

    }
};
struct Lazy {

    void Reset() const {

    }
    bool HaveTag() const {

    }
};
struct Node {
    Info val;
    Lazy lz;
} seg[MAX_N * 4];

__attribute__ ((__always_inline__))
void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
__attribute__ ((__always_inline__))
void update(int l, int r, int id, const Lazy &lz) {

}
__attribute__ ((__always_inline__))
void down(int l, int r, int id) {
    if (auto &lz = seg[id].lz; lz.HaveTag()) {
        auto mid = l + (r - l) / 2;
        update(l, mid, id * 2, lz);
        update(mid + 1, r, id * 2 + 1, lz);
        lz.Reset();
    }
}

void build(int l, int r, int id, const auto &a) {
    if (l == r) {

    } else {
        auto mid = l + (r - l) / 2;
        build(l, mid, id * 2, a);
        build(mid + 1, r, id * 2 + 1, a);
        rise(id);
    }
}
void apply(int l, int r, int id, int ml, int mr, const Lazy &lz) {
    if (l == ml && r == mr) {
        update(l, r, id, lz);
    } else {
        auto mid = l + (r - l) / 2;
        down(l, r, id);
        if (mr <= mid) {
            apply(l, mid, id * 2, ml, mr, lz);
        } else if (ml > mid) {
            apply(mid + 1, r, id * 2 + 1, ml, mr, lz);
        } else {
            apply(l, mid, id * 2, ml, mid, lz);
            apply(mid + 1, r, id * 2 + 1, mid + 1, mr, lz);
        }
        rise(id);
    }
}

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + (r - l) / 2;
        down(l, r, id);
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 + 1, ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}
// clang-format on