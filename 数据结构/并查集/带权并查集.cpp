#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = int64_t;

template <typename Vector>
#ifdef __cpp_concepts
    requires requires(Vector a, Vector b) {
        { a + b } -> std::same_as<Vector>;
        { -a } -> std::same_as<Vector>;
        { a += b };
    }
#endif
class WeidgeDisjointSet {
private:
    std::vector<int> _leader;
    std::vector<Vector> _vector;

public:
    using vector_type = Vector;
    using value_type = Vector;

private:
    static void _IotaInitLeader(std::vector<int> &leader) {
        std::iota(leader.begin(), leader.end(), 0);
    }

public:
    explicit WeidgeDisjointSet(std::size_t size, Vector vec)
        : _leader(size), _vector(size, vec) {
        _IotaInitLeader(_leader);
    }

    int GetLeader(int x) {
        if (_leader[x] == x) {
            return x;
        }
        int fa = _leader[x];
        _leader[x] = GetLeader(_leader[x]);
        _vector[x] += _vector[fa];
        return _leader[x];
    }

    bool MergeTo(int from, int to, Vector vec) {
        int ra = GetLeader(from), rb = GetLeader(to);
        if (ra == rb) {
            return false;
        }
        _vector[ra] = -_vector[from] + vec + _vector[to];
        _leader[ra] = rb;
        return true;
    }

    bool IsSame(int a, int b) noexcept {
        return GetLeader(a) == GetLeader(b);
    }

    Vector Ask(int from, int to) const {
        return _vector[from] + -_vector[to];
    }

    void Assign(std::size_t size, Vector vec) {
        _leader.resize(size);
        _IotaInitLeader(_leader);
        _vector.assign(size, vec);
    }
};

struct Vector {
    i64 val;

    constexpr Vector(i64 v = 0) : val(v) {}

    friend constexpr Vector operator+(const Vector &a, const Vector &b) {
        return Vector{a.val + b.val};
    }

    constexpr Vector &operator+=(const Vector &o) {
        *this = *this + o;
        return *this;
    }

    constexpr Vector operator-() const {
        return Vector{-val};
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;
    WeidgeDisjointSet<Vector> dsu(n, 0);

    for (int t = 0; t < q; t++) {
        int opt, u, v;
        std::cin >> opt >> u >> v;
        if (opt == 0) {
            i64 w;
            std::cin >> w;
            dsu.MergeTo(u, v, w);
        } else {
            if (!dsu.IsSame(u, v)) {
                std::cout << "?\n";
            } else {
                auto ret = dsu.Ask(u, v);
                std::cout << ret.val << '\n';
            }
        }
    }
}
