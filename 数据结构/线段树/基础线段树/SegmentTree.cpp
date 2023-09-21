#include <bits/stdc++.h>

struct InfoImpl {};

template <typename __Info, typename __Opt> class SegmentTree {
public:
    using value_type = __Info;
    using opt_type = __Opt;

private:
    std::vector<value_type> _node;
    opt_type _opt;
    std::size_t _n;

private:
    static constexpr std::size_t _root = 0;

private:
    static constexpr std::size_t _GetLeftId(std::size_t id) noexcept {
        return id * 2 + 1;
    }
    static constexpr std::size_t _GetRightId(std::size_t id) noexcept {
        return id * 2 + 2;
    }

public:
    explicit SegmentTree(std::size_t n, __Info value, __Opt opt)
        : _node(n * 4, value), _opt(std::move(opt)), _n(n) {}

    template <typename Iter, typename Opt>
    explicit SegmentTree(Iter first, Iter last, Opt opt)
        : SegmentTree(std::distance(first, last),
                      (typename std::iterator_traits<Iter>::value_type){},
                      std::move(opt)) {
        Build(first, last);
    }

private:
    template <typename Iter>
    void _Build(std::size_t l, std::size_t r, std::size_t id, Iter first,
                Iter last) {
        if (r - l == 1) {
            _node[id] = *first;
        } else {
            auto mid = l + (r - l) / 2;
            _Build(l, mid, _GetLeftId(id), first, first + (r - l) / 2);
            _Build(mid, r, _GetRightId(id), first + (r - l) / 2, last);
            _node[id] = _opt(_node[_GetLeftId(id)], _node[_GetRightId(id)]);
        }
    }

public:
    template <typename Iter> void Build(Iter first, Iter last) {
        _Build(0, _n, _root, first, last);
    }

private:
    __Info _RangeQuery(std::size_t l, std::size_t r, std::size_t id,
                       std::size_t ql, std::size_t qr) {
        if (r - l == 1) {
            return _node[id];
        } else {
            auto mid = l + (r - l) / 2;
            if (qr <= mid) {
                return _RangeQuery(l, mid, _GetLeftId(id), ql, qr);
            } else if (ql >= mid) {
                return _RangeQuery(mid, qr, _GetRightId(id), ql, qr);
            } else {
                return _opt(_RangeQuery(l, mid, _GetLeftId(id), ql, mid),
                            _RangeQuery(mid, r, _GetRightId(id), mid, qr));
            }
        }
    }

public:
    __Info RangeQuery(std::size_t ql, std::size_t qr) {
        return _RangeQuery(0, _n, _root, ql, qr);
    }

private:
    template <typename T, typename ActionOpt>
    void _Action(std::size_t l, std::size_t r, std::size_t id,
                 std::size_t target, T value, ActionOpt &&action) {
        if (r - l == 1) {
            _node[id] = action(_node[id], value);
        } else {
            auto mid = l + (r - l) / 2;
            if (target < mid) {
                _Action(l, mid, _GetLeftId(id), target, value, action);
            } else {
                _Action(mid, r, _GetRightId(id), target, value, action);
            }
            _node[id] = _opt(_node[_GetLeftId(id)], _node[_GetRightId(id)]);
        }
    }

public:
    template <typename T, typename ActionOpt>
    void Action(std::size_t target, T value, ActionOpt &&action) {
        _Action(0, _n, _root, target, value, action);
    }
};

template <typename Container, typename Opt>
explicit SegmentTree(const Container &, Opt)
    -> SegmentTree<typename Container::value_type, Opt>;
