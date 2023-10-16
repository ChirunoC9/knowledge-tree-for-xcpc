#include <cassert>
#include <concepts>
#include <numeric>
#include <vector>

class DisjointSet {
private:
    std::vector<int> _lead;
    std::size_t _set_count;

public:
    explicit DisjointSet(std::size_t size)
        : _lead(size, -1), _set_count(size) {}

private:
    auto _InRange(int x) const noexcept -> bool {
        return 0 <= x && x < (int)_lead.size();
    }

    auto _Leader(int x) -> int {
        if (_lead[x] <= -1) {
            return x;
        }
        return _lead[x] = _Leader(_lead[x]);
    }

    auto _Count(int x) -> int {
        return -_lead[_Leader(x)];
    }

    template <std::strict_weak_order<int, int> _BinaryCompare>
    auto _MergeIf(int a, int b, const _BinaryCompare &comp) -> bool {
        a = _Leader(a);
        b = _Leader(b);
        if (!comp(a, b)) {
            std::swap(a, b);
        }
        if (!comp(a, b)) {
            return false;
        }
        _lead[a] += _lead[b];
        _lead[b] = a;
        --_set_count;
        return true;
    }

    auto _MergeTo(int from, int to) noexcept -> bool {
        from = _Leader(from);
        to = _Leader(to);
        if (from == to) {
            return false;
        }
        _lead[to] += _lead[from];
        _lead[from] = to;
        --_set_count;
        return true;
    }

public:
    auto Leader(int x) -> int {
        assert(_InRange(x));
        return _Leader(x);
    }

    auto IsLeader(int x) -> bool {
        return Leader(x) != x;
    }

    auto Count() const noexcept -> std::size_t {
        return _set_count;
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
        return _Leader(a) == _Leader(b);
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
        std::fill(_lead.begin(), _lead.end(), -1);
    }

    auto Assign(std::size_t size) -> void {
        _lead.assign(size, -1);
        _set_count = size;
    }
};
