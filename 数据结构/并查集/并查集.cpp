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

class disjoint_set_union {
public:
    explicit disjoint_set_union(int __n)
        : __leader(__n, -1), __remain_sets_count(__n) {

    }
    
    int get_leader(int __x) {
        assert(__vertex_in_range(__x));
        return __get_leader(__x);
    }
    
    // merge_a_to_b
    bool merge_to(int __a, int __b) {
        assert(__vertex_in_range(__a));
        assert(__vertex_in_range(__b));
        __a = get_leader(__a);
        __b = get_leader(__b);
        if (__a == __b)
            return false;
        __merge_a_to_b(__a, __b);
        return true;
    }

    int get_remain_sets_count() const noexcept {
        return __remain_sets_count;
    }

    int get_set_size(int __x) {
        assert(__vertex_in_range(__x));
        auto __x_leader = get_leader(__x);
        return -__leader[__x_leader];
    }

    void assign(int __new_size) {
        __leader.assign(__new_size, -1);
        __remain_sets_count = __new_size;
    }

private:
    // bool __vertex_in_range(int __x) const {
    // }

    bool __vertex_in_range(int __x) const {
        return 0 <= __x && __x < (int)__leader.size();
    }

    int __get_leader(int __x) {
        if (__leader[__x] <= -1) 
            return __x;
        return __leader[__x] = __get_leader(__leader[__x]);
    }

    void __merge_a_to_b(int __a, int __b) {
        __leader[__b] += __leader[__a];
        __leader[__a] = __b;
        -- __remain_sets_count;
    }

private:
    std::vector<int> __leader;
    int __remain_sets_count;
};