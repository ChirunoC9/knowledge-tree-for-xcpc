# AcWing 246. 区间最大公约数

## 题意

给定一个长度为 $n$ 的数列 $a$ ，以及 $q$ 次操作。每次操作输入格式如下。

- `Q l r` 表示查询区间 $[l,r]$ 的最大公因数；
- `C l r d` 表示对区间 $[l, r]$ 的所有数字都加上 $d$ 。

## 思路

由欧几里得定理可得，$\gcd(a, b) = \gcd(b, a \bmod b) = \gcd(b, a - b)$ ，换成我们所需要的，就是 $\gcd(a, b) = \gcd(a, b - a)$ 。转换为更多数字，则为 $\gcd(a, b, c) = \gcd(a, b - a, c - b)$ 。

可以发现，数列的 $\gcd$ 与其一次差分数列的 $\gcd$ 一样。对于区间加这一操作，差分后则对应为 $l$ 位置加，$r$ 位置减去。

因此，我们可以维护 $a$ 的差分数组 $b$ 的区间 $\gcd$ ，那么查询则变为 $\gcd(a_l, a_{l+1}, \cdots, a_{r}) = \gcd(a_l, b_{l+1}, \cdots, b_{r}) = \gcd(\sum_{i=1}^l b_i , b_{l+1}, \cdots, b_{r})$ 。因此，我们还要维护差分数组的区间和，但是这个区间和作为查询差分数组的前缀和使用。

对于区间加，在差分数组上体现则是两个端点加加减减。

```cpp
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
```
