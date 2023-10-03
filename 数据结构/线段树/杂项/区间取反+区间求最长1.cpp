#include <bits/stdc++.h>

template <typename _Ty>
constexpr _Ty inf = std::numeric_limits<_Ty>::max() / 2;
using u8 = uint8_t;
using i64 = int64_t;

using namespace std;

const int N = 5e5 + 10;

// const int N = 100;
struct Base {
    int len, pre, suf;
};
struct Info {
    int l, r;
    Base z, o;
    auto swap() {
        std::swap(z, o);
    }
    auto Len() const {
        return r - l + 1;
    }
    friend Info operator+(const Info &a, const Info &b) {
        Info ret;
        ret.l = a.l;
        ret.r = b.r;

        ret.z.pre = a.Len() == a.z.len ? a.Len() + b.z.pre : a.z.pre;
        ret.z.suf = b.Len() == b.z.len ? b.Len() + a.z.suf : b.z.suf;

        ret.o.pre = a.Len() == a.o.len ? a.Len() + b.o.pre : a.o.pre;
        ret.o.suf = b.Len() == b.o.len ? b.Len() + a.o.suf : b.o.suf;

        ret.z.len = max({a.z.len, b.z.len, a.z.suf + b.z.pre});
        ret.o.len = max({a.o.len, b.o.len, a.o.suf + b.o.pre});

        return ret;
    }
};
struct Node {
    Info val;
    int rev;
} seg[N * 4];

void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void update(int id) {
    seg[id].val.swap();
    seg[id].rev ^= 1;
}

void down(int id) {
    auto &rev = seg[id].rev;
    if (rev) {
        update(id * 2);
        update(id * 2 + 1);
        rev = 0;
    }
}

void build(int l, int r, int id, auto &seq) {
    seg[id].val.l = l;
    seg[id].val.r = r;
    seg[id].rev = 0;
    if (l == r) {
        int x = seq[l] == '1';
        seg[id].val.z.pre = seg[id].val.z.suf = seg[id].val.z.len = x == 0;
        seg[id].val.o.pre = seg[id].val.o.suf = seg[id].val.o.len = x == 1;
    } else {
        int mid = l + (r - l) / 2;
        build(l, mid, id * 2, seq);
        build(mid + 1, r, id * 2 + 1, seq);
        rise(id);
    }
}

void modify(int l, int r, int id, int ml, int mr) {
    if (l == ml && r == mr) {
        update(id);
    } else {
        int mid = l + (r - l) / 2;
        down(id);
        if (mr <= mid) {
            modify(l, mid, id * 2, ml, mr);
        } else if (ml > mid) {
            modify(mid + 1, r, id * 2 + 1, ml, mr);
        } else {
            modify(l, mid, id * 2, ml, mid);
            modify(mid + 1, r, id * 2 + 1, mid + 1, mr);
        }
        rise(id);
    }
}

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + (r - l) / 2;
        down(id);
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 + 1, ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid) +
                   query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}

auto Main() -> void {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    s = ' ' + s;

    build(1, n, 1, s);

    for (int t = 0; t < q; t += 1) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 1) {
            modify(1, n, 1, l, r);
        } else {
            auto ret = query(1, n, 1, l, r);
            cout << ret.o.len << '\n';
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
