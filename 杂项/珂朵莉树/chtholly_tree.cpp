#include "bits/stdc++.h"

template <typename __type> class chtholly_tree {
private:
    std::map<int, __type> mp;

public:
    using type = __type;

public:
    explicit chtholly_tree(int _first, const __type &__init_value)
        : mp{{_first - 1, __init_value}} {}

    void reset(int _first, const __type &__init_value) {
        mp.clear();
        mp[_first - 1] = __init_value;
    }

    void split(int pos) {
        auto it = std::prev(mp.upper_bound(pos));
        mp[pos] = it->second;
    }

    void split(int pl, int pr) {
        split(pl);
        split(pr);
    }

    auto get_pos_iter(int pos) { return mp.find(pos); }

    void assign(int l, int r, const __type &value) {
        split(l, r);
        auto it = get_pos_iter(l);
        while (it->first != r)
            it = mp.erase(it);
        mp[l] = value;
    }
};
