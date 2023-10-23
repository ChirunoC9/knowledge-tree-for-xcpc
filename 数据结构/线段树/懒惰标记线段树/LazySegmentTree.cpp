#include <iostream>
#include <numeric>
#include <vector>

#include <concepts>

template <typename _NodeImpl>
    requires requires(typename _NodeImpl::Info left,
                      typename _NodeImpl::Info right,
                      typename _NodeImpl::Lazy lz) {
        {
            _NodeImpl::Merge(left, right)
        } -> std::same_as<typename _NodeImpl::Info>;

        {
            _NodeImpl::ApplyInfo(left, lz)
        } -> std::same_as<typename _NodeImpl::Info>;

        {
            _NodeImpl::ApplyTag(lz, lz)
        } -> std::same_as<typename _NodeImpl::Lazy>;

        { lz.HaveTag() } -> std::same_as<bool>;

        { lz.ResetTag() };
    }
class LazySegTree {
private:
    using _Impl = _NodeImpl;
    using _Info = typename _NodeImpl::Info;
    using _Lazy = typename _NodeImpl::Lazy;

public:
    using info_type = _Info;
    using lazy_type = _Lazy;

private:
    struct _Node {
        _Info val;
        _Lazy lz;
    };

private:
    std::vector<_Node> _seg;
    std::size_t _n;

private:
    inline static constexpr std::size_t _ROOT = 1;

    __always_inline static constexpr auto _LeftChild(std::size_t index)
        -> std::size_t {
        return index * 2;
    }
    __always_inline static constexpr auto _RightChild(std::size_t index)
        -> std::size_t {
        return index * 2 + 1;
    }

public:
    explicit LazySegTree(std::size_t seg_node_count)
        : _seg(seg_node_count * 4), _n(seg_node_count) {}

private:
    __always_inline auto _Raise(int id) -> void {
        _seg[id].val =
            _Impl::Merge(_seg[_LeftChild(id)].val, _seg[_RightChild(id)].val);
    }

    __always_inline auto _Update(int id, const _Lazy &lz) -> void {
        _seg[id].val = _Impl::ApplyInfo(_seg[id].val, lz);
        _seg[id].lz = _Impl::ApplyTag(_seg[id].lz, lz);
    }

    __always_inline auto _Down(int id) -> void {
        if (auto &lz = _seg[id].lz; lz.HaveTag()) {
            _Update(_LeftChild(id), lz);
            _Update(_RightChild(id), lz);
            lz.ResetTag();
        }
    }

    auto _Apply(int l, int r, int id, int ml, int mr, const _Lazy &lz) -> void {
        if (l == ml && r == mr) {
            _Update(id, lz);
        } else {
            auto mid = std::midpoint(l, r);
            _Down(id);
            if (mr <= mid) {
                _Apply(l, mid, _LeftChild(id), ml, mr, lz);
            } else if (ml >= mid) {
                _Apply(mid, r, _RightChild(id), ml, mr, lz);
            } else {
                _Apply(l, mid, _LeftChild(id), ml, mid, lz);
                _Apply(mid, r, _RightChild(id), mid, mr, lz);
            }
            _Raise(id);
        }
    }

    auto _GetInfo(int l, int r, int id, int ql, int qr) -> _Info {
        if (l == ql && r == qr) {
            return _seg[id].val;
        } else {
            auto mid = std::midpoint(l, r);
            _Down(id);
            if (qr <= mid) {
                return _GetInfo(l, mid, _LeftChild(id), ql, qr);
            } else if (ql >= mid) {
                return _GetInfo(mid, r, _RightChild(id), ql, qr);
            } else {
                return _Impl::Merge(_GetInfo(l, mid, _LeftChild(id), ql, mid),
                                    _GetInfo(mid, r, _RightChild(id), mid, qr));
            }
        }
    }

    auto _SetPosInfo(int l, int r, int id, int target, const _Info &unit_val)
        -> void {
        if (l + 1 == r) {
            _seg[id].val = unit_val;
        } else {
            auto mid = std::midpoint(l, r);
            _Down(id);
            if (target < mid) {
                _SetPosInfo(l, mid, _LeftChild(id), target, unit_val);
            } else {
                _SetPosInfo(mid, r, _RightChild(id), target, unit_val);
            }
            _Raise(id);
        }
    }

    template <typename RandomAccessIter, typename CoverFunc>
        requires requires(CoverFunc cover, int l, int r,
                          RandomAccessIter iter) {
            { cover(l, r, *iter) } -> std::same_as<_Info>;
        }
    auto _RangeBuild(int l, int r, int id, RandomAccessIter first,
                     RandomAccessIter last, const CoverFunc &cover) -> void {
        _seg[id].lz.ResetTag();
        if (l + 1 == r) {
            _seg[id].val = cover(l, r, *first);
            return;
        }
        auto mid = std::midpoint(l, r);
        auto mid_it = first + (last - first) / 2;
        _RangeBuild(l, mid, _LeftChild(id), first, mid, cover);
        _RangeBuild(mid, r, _RightChild(id), mid, last, cover);
        _Raise(id);
    }

public:
    auto Apply(int ml, int mr, const _Lazy &lazy) -> void {
        if (ml >= mr)
            return;
        _Apply(0, _n, _ROOT, ml, mr, lazy);
    }

    auto GetInfo(int ql, int qr) -> _Info {
        if (ql >= qr)
            return _Info{};
        return _GetInfo(0, _n, _ROOT, ql, qr);
    }

    auto SetPosInfo(int target, const _Info &unit_val) -> void {
        _SetPosInfo(0, _n, _ROOT, target, unit_val);
    }

    template <typename RandomAccessIter, typename CoverFunc>
        requires requires(CoverFunc cover, int l, int r,
                          RandomAccessIter iter) {
            { cover(l, r, *iter) } -> std::same_as<_Info>;
        }
    auto RangeBuild(RandomAccessIter first, RandomAccessIter last,
                    const CoverFunc &cover) -> void {
        assert(std::distance(first, last) == _n);
        _RangeBuild(0, _n, first, last, cover);
    }
};

using i64 = int64_t;

template <typename _Info, typename _Lazy>
struct _NodeImpl {
    using Info = _Info;
    using Lazy = _Lazy;

    __always_inline constexpr static auto Merge(const Info &left,
                                                const Info &right) -> Info;

    __always_inline constexpr static auto ApplyInfo(const Info &a,
                                                    const Lazy &lz) -> Info;

    __always_inline constexpr static auto ApplyTag(const Lazy &left,
                                                   const Lazy &right) -> Lazy;
};

struct Info {
    int l, r;
    i64 val;
    constexpr Info(int l = {}, int r = {}, i64 val = {})
        : l(l), r(r), val(val) {}
    constexpr int len() const {
        return r - l;
    }
};
struct Lazy {
    i64 add;
    constexpr Lazy(i64 add = {}) : add(add) {}
    bool HaveTag() const {
        return add != 0;
    }
    void ResetTag() {
        add = 0;
    }
};

template <>
__always_inline constexpr auto _NodeImpl<Info, Lazy>::Merge(const Info &left,
                                                            const Info &right)
    -> Info {
    return Info{left.l, right.r, left.val + right.val};
}

template <>
__always_inline constexpr auto _NodeImpl<Info, Lazy>::ApplyInfo(const Info &a,
                                                                const Lazy &lz)
    -> Info {
    return Info{a.l, a.r, a.val + lz.add & a.len()};
}

template <>
__always_inline constexpr auto
_NodeImpl<Info, Lazy>::ApplyTag(const Lazy &left, const Lazy &right) -> Lazy {
    return Lazy{left.add + right.add};
}

struct NodeImpl {
    struct Info {
        int l, r;
        i64 val;
        Info(int l = {}, int r = {}, i64 val = {}) : l(l), r(r), val(val) {}
        int len() const {
            return r - l;
        }
    };
    struct Lazy {
        i64 add;
        Lazy(i64 add = {}) : add(add) {}
        bool HaveTag() const {
            return add != 0;
        }
        void ResetTag() {
            add = 0;
        }
    };

    __always_inline static Info Merge(Info left, Info right) {
        return Info{left.l, right.r, left.val + right.val};
    }

    __always_inline static Info ApplyInfo(Info a, Lazy lz) {
        a.val += lz.add * a.len();
        return a;
    }

    __always_inline static Lazy ApplyTag(Lazy a, Lazy b) {
        return Lazy{a.add + b.add};
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    LazySegTree<NodeImpl> seg(n);

    for (int i = 0; i < n; i += 1) {
        i64 x;
        std::cin >> x;
        seg.SetPosInfo(i, {i, i + 1, x});
    }

    for (int t = 0; t < q; t += 1) {
        int opt;
        std::cin >> opt;

        if (opt == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            l -= 1;
            seg.Apply(l, r, k);
        } else {
            int l, r;
            std::cin >> l >> r;
            l -= 1;
            std::cout << seg.GetInfo(l, r).val << '\n';
        }
    }
}