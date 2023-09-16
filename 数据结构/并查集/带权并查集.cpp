#include <numeric>
#include <vector>

template <typename Vector> class WeidgeDisjoinSetUnion {
private:
    std::vector<int> _leader;
    std::vector<Vector> _vector;

public:
    explicit WeidgeDisjoinSetUnion(std::size_t size, Vector vec)
        : _leader(size), _vector(size, vec) {
        std::iota(_leader.begin(), _leader.end(), 0);
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

    bool MergeTo(int a, int b, Vector vec) {
        int ra = GetLeader(a), rb = GetLeader(b);
        if (ra == rb) {
            return false;
        }
        _vector[ra] = -_vector[a] + vec + _vector[b];
        _leader[ra] = rb;
        return true;
    }

    bool IsSame(int a, int b) { return GetLeader(a) == GetLeader(b); }

    Vector Ask(int a, int b) const {
        assert(IsSame(a, b));
        return _vector[a] + -_vector[b];
    }

    void Assign(std::size_t size, Vector vec) {
        _leader.resize(size);
        std::iota(_leader.begin(), _leader.end(), 0);
        _vector.assign(size, vec);
    }
};
