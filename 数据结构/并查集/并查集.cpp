#include <bits/stdc++.h>

class DisjointSetUnion {
public:
    DisjointSetUnion(int size) 
        : dad(size, -1), count{size} {}

    int Find(int x) {
        if (dad[x] <= -1) {
            return x;
        }
        return dad[x] = Find(dad[x]);
    }

    int operator [] (int x) {
        return Find(x);
    }

    bool Merge(int a, int b) {
        a = Find(a); b = Find(b);
        if (a == b)
            return false;
        if (a > b)
            std::swap(a, b); 
        dad[a] += dad[b];
        dad[a] = b;
        -- count;
        return true;
    }

    bool IsSame(int a, int b) {
        return Find(a) == Find(b);
    }

    void Assign(int size, int value = -1) {
        dad.assign(size, value);
        count = size;
    }

    void ReSet() {
        std::fill(std::begin(dad), std::end(dad), -1);
        count = dad.size();
    }

    int Count(int x) {
        return -dad[Find(x)];
    }

    int Count() const {
        return count;
    }

private:
    std::vector<int> dad;
    int count;
};

class disjoin_set_union {
private:
    std::vector<int> dad;
    std::size_t set_count;

public:
    explicit disjoin_set_union(std::size_t __size) 
        : dad(__size, -1), set_count(__size) {
        
    }

private:
    int __get_leader(int __x) {
        if (dad[__x] <= 1) {
            return __x;
        }
        return dad[__x] = __get_leader(dad[__x]);
    }

    int __get_count(int __x) {
        return -dad[__get_leader(__x)];
    }

    template <typename __compare>
    bool __merge_if(int __a, int __b, const __compare &comp) {
        __a = __get_leader(__a);
        __b = __get_leader(__b);
        if (!comp(__a, __b)) {
            std::swap(__a, __b);
        }
        if (!comp(__a, __b)) {
            return false;
        }
        dad[__a] += dad[__b];
        dad[__b] = __a;
        -- set_count;
        return true;
    }

public:
    int get_leader(int __x) {
        assert(0 <= __x && __x < (int)dad.size());
        return __get_leader(__x);
    }

    int get_count() const {
        return set_count;
    }

    int get_count(int __x) {
        assert(0 <= __x && __x < (int)dad.size());
        return __get_count(__x);
    }

    template <typename __compare>
    bool merge_if(int __a, int __b, const __compare &__comp) {
        assert(0 <= __a && __a < (int)dad.size());
        assert(0 <= __b && __b < (int)dad.size());
        return __merge_if(__a, __b, __comp);
    }

    bool merge(int __a, int __b) {
        assert(0 <= __a && __a < (int)dad.size());
        assert(0 <= __b && __b < (int)dad.size());
        return __merge_if(__a, __b, std::less<int>{});
    }

    void assign(std::size_t __size) {
        dad.assign(__size, -1);
        set_count = __size;
    }
};