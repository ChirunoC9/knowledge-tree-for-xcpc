#include "bits/stdc++.h"

template <typename __type> class ChthollyTree {
private:
    std::map<int, __type> _mp;

public:
    using ValueType = __type;

public:
    explicit ChthollyTree(int __first, const __type &__init_value)
        : _mp{{__first - 1, __init_value}} {}

    void Reset(int __first, const __type &__init_value) {
        _mp.clear();
        _mp[__first - 1] = __init_value;
    }

    void Split(int __pos) {
        auto targetIter = std::prev(_mp.upper_bound(__pos));
        _mp[__pos] = targetIter->second;
    }

    // [l, r]
    void Split(int __pos_l, int __pos_r) {
        Split(__pos_l);
        Split(__pos_r);
    }

    auto GetPosIter(int __pos) { return _mp.find(__pos); }

    void Assign(int __l, int __r, const __type &__value) {
        Split(__l, __r);
        auto it = GetPosIter(__l);
        while (it->first != __r)
            it = _mp.erase(it);
        _mp[__l] = __value;
    }
};
