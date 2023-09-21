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
    bool _InRange(int x) const noexcept { return 0 <= x && x < _leader.size(); }

    int _GetLeader(int x) {
        if (_leader[x] <= -1) {
            return x;
        }
        return _leader[x] = _GetLeader(_leader[x]);
    }

    int _GetCount(int x) { return -_leader[_GetLeader(x)]; }

    template <std::strict_weak_order<int, int> Compare>
    bool _MergeIf(int a, int b, const Compare &comp) {
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

    bool _MergeTo(int a, int b) noexcept {
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
    int GetLeader(int x) {
        assert(_InRange(x));
        return _GetLeader(x);
    }

    int GetCount() const noexcept { return _setCount; }

    int GetCount(int x) {
        assert(_InRange(x));
        return _GetCount(x);
    }

    template <std::strict_weak_order<int, int> Compare>
    bool MergeIf(int a, int b, const Compare &comp) {
        assert(_InRange(a));
        assert(_InRange(b));
        return _MergeIf(a, b, comp);
    }

    bool MergeTo(int a, int b) {
        assert(_InRange(a));
        assert(_InRange(b));
        return _MergeTo(a, b);
    }

    bool IsSame(int a, int b) {
        assert(_InRange(a));
        assert(_InRange(b));
        return _GetLeader(a) == _GetLeader(b);
    }

    void Assign(std::size_t size) {
        _leader.assign(size, -1);
        _setCount = size;
    }
};
