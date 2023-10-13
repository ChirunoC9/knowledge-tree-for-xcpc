#include <cassert>
#include <concepts>
#include <numeric>
#include <vector>

class DisjointSet {
private:
    std::vector<int> _leader;
    std::size_t _setCount;

public:
    explicit DisjointSet(std::size_t size)
        : _leader(size, -1), _setCount(size) {}

private:
    auto _InRange(int x) const noexcept -> bool {
        return 0 <= x && x < (int)_leader.size();
    }

    auto _GetLeader(int x) -> int {
        if (_leader[x] <= -1) {
            return x;
        }
        return _leader[x] = _GetLeader(_leader[x]);
    }

    auto _Count(int x) -> int {
        return -_leader[_GetLeader(x)];
    }

    template <std::strict_weak_order<int, int> _BinaryCompare>
    auto _MergeIf(int a, int b, const _BinaryCompare &comp) -> bool {
        a = _GetLeader(a);
        b = _GetLeader(b);
        if (!comp(a, b)) {
            std::swap(a, b);
        }
        if (!comp(a, b)) {
            return false;
        }
        _leader[a] += _leader[b];
        _leader[b] = a;
        --_setCount;
        return true;
    }

    auto _MergeTo(int from, int to) noexcept -> bool {
        from = _GetLeader(from);
        to = _GetLeader(to);
        if (from == to) {
            return false;
        }
        _leader[to] += _leader[from];
        _leader[from] = to;
        --_setCount;
        return true;
    }

public:
    auto GetLeader(int x) -> int {
        assert(_InRange(x));
        return _GetLeader(x);
    }

    auto IsLeader(int x) -> bool {
        return GetLeader(x) != x;
    }

    auto Count() const noexcept -> std::size_t {
        return _setCount;
    }

    auto Count(int x) -> int {
        assert(_InRange(x));
        return _Count(x);
    }

    template <std::strict_weak_order<int, int> _BinaryCompare>
    auto MergeIf(int a, int b, const _BinaryCompare &comp) -> bool {
        assert(_InRange(a));
        assert(_InRange(b));
        return _MergeIf(a, b, comp);
    }

    auto MergeTo(int from, int to) -> bool {
        assert(_InRange(from));
        assert(_InRange(to));
        return _MergeTo(from, to);
    }

    auto Merge(int from, int to) -> bool {
        return MergeTo(from, to);
    }

    auto IsSame(int a, int b) -> bool {
        assert(_InRange(a));
        assert(_InRange(b));
        return _GetLeader(a) == _GetLeader(b);
    }

    auto IsSame(std::initializer_list<int> input_list) -> bool {
        if (input_list.size() == 0)
            return true;
        bool ret = true;
        int v = *input_list.begin();
        for (auto x : input_list) {
            ret = IsSame(v, x);
            if (!ret)
                break;
        }
        return ret;
    }

    template <typename _InputIterator>
        requires std::input_iterator<_InputIterator> &&
                 std::same_as<
                     typename std::iterator_traits<_InputIterator>::value_type,
                     int>
    auto IsSame(_InputIterator first, _InputIterator last) -> bool {
        auto _dis = std::distance(first, last);
        if (_dis == 0)
            return true;
        bool ret = true;
        int v = *first;
        for (auto it = first + 1; it != last && ret; ++it) {
            ret = IsSame(v, *it);
        }
        return ret;
    }

    auto Assign() -> void {
        std::fill(_leader.begin(), _leader.end(), -1);
    }

    auto Assign(std::size_t size) -> void {
        _leader.assign(size, -1);
        _setCount = size;
    }
};
