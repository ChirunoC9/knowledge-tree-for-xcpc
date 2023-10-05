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

    auto _GetCount(int x) -> int {
        return -_leader[_GetLeader(x)];
    }

    template <std::strict_weak_order<int, int> _Compare>
    auto _MergeIf(int a, int b, const _Compare &comp) -> bool {
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

    auto _MergeTo(int a, int b) noexcept -> bool {
        a = _GetLeader(a);
        b = _GetLeader(b);
        if (a == b) {
            return false;
        }
        _leader[b] += _leader[a];
        _leader[a] = b;
        --_setCount;
        return true;
    }

public:
    auto GetLeader(int x) -> int {
        assert(_InRange(x));
        return _GetLeader(x);
    }

    auto IsLeader(int x) const -> bool {
        return _leader[x] <= -1;
    }

    auto GetCount() const noexcept -> std::size_t {
        return _setCount;
    }

    auto GetCount(int x) -> int {
        assert(_InRange(x));
        return _GetCount(x);
    }

    template <std::strict_weak_order<int, int> _Compare>
    auto MergeIf(int a, int b, const _Compare &comp) -> bool {
        assert(_InRange(a));
        assert(_InRange(b));
        return _MergeIf(a, b, comp);
    }

    auto MergeTo(int a, int b) -> bool {
        assert(_InRange(a));
        assert(_InRange(b));
        return _MergeTo(a, b);
    }

    auto IsSame(int a, int b) -> bool {
        assert(_InRange(a));
        assert(_InRange(b));
        return _GetLeader(a) == _GetLeader(b);
    }

    auto IsSame(std::initializer_list<int> list) -> bool {
        bool ret = true;
        int v = *list.begin();
        for (auto x : list) {
            ret = IsSame(v, x);
            if (!ret)
                break;
        }
        return ret;
    }

    template <typename _Iter>
        requires std::input_iterator<_Iter> &&
                 std::same_as<typename std::iterator_traits<_Iter>::value_type,
                              int>
    auto IsSame(_Iter first, _Iter last) {
        bool ret = true;
        int v = *first;
        for (auto it = first + 1; it != last && ret; ++it) {
            ret = IsSame(v, *it);
        }
        return ret;
    }

    auto Assign(std::size_t size) -> void {
        _leader.assign(size, -1);
        _setCount = size;
    }
};
