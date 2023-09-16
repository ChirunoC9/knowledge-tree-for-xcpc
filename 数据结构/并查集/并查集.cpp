#include <bits/stdc++.h>

class DisjoinSetUnion {
private:
    std::vector<int> _leader;
    std::size_t _setCount;

public:
    explicit DisjoinSetUnion(std::size_t __size)
        : _leader(__size, -1), _setCount(__size) {}

private:
    bool _InRange(int __x) const { return 0 <= __x && __x < _leader.size(); }

    int _GetLeader(int __x) {
        if (_leader[__x] <= -1) {
            return __x;
        }
        return _leader[__x] = _GetLeader(_leader[__x]);
    }

    int _GetCount(int __x) { return -_leader[_GetLeader(__x)]; }

    template <typename __compare>
    bool _MergeIf(int __a, int __b, const __compare &comp) {
        __a = _GetLeader(__a);
        __b = _GetLeader(__b);
        if (!comp(__a, __b)) {
            std::swap(__a, __b);
        }
        if (!comp(__a, __b)) {
            return false;
        }
        _leader[__a] += _leader[__b];
        _leader[__b] = __a;
        --_setCount;
        return true;
    }

    bool _MergeTo(int __a, int __b) {
        __a = _GetLeader(__a);
        __b = _GetLeader(__b);
        if (__a == __b) {
            return false;
        }
        _leader[__b] += _leader[__a];
        _leader[__a] = __b;
        --_setCount;
        return true;
    }

public:
    int GetLeader(int __x) {
        assert(_InRange(__x));
        return _GetLeader(__x);
    }

    int GetCount() const { return _setCount; }

    int GetCount(int __x) {
        assert(_InRange(__x));
        return _GetCount(__x);
    }

    template <typename __compare>
    bool MergeIf(int __a, int __b, const __compare &__comp) {
        assert(_InRange(__a));
        assert(_InRange(__b));
        return _MergeIf(__a, __b, __comp);
    }

    bool MergeTo(int __a, int __b) {
        assert(_InRange(__a));
        assert(_InRange(__b));
        return _MergeTo(__a, __b);
    }

    bool IsSame(int __a, int __b) {
        assert(_InRange(__a));
        assert(_InRange(__b));
        return _GetLeader(__a) == _GetLeader(__b);
    }

    void Assign(std::size_t __size) {
        _leader.assign(__size, -1);
        _setCount = __size;
    }
};
