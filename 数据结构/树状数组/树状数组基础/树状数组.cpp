#include <bits/stdc++.h>

#if __cplusplus >= 202002L
template <typename _Ty,
          std::regular_invocable<_Ty, _Ty> _Operator = std::plus<_Ty>>
#else
template <typename Type, typename Operator = std::plus<Type>,
          typename = std::enable_if<
              std::is_invocable<Operator, Type, Type>::value>::type>
#endif
class FenwickTree {
public:
    using value_type = _Ty;
    using operator_type = _Operator;

private:
    inline constexpr static auto _Lowbit(int x) noexcept -> int {
        return x & -x;
    }

    std::vector<_Ty> _bit;
    _Operator _opt;

public:
    explicit FenwickTree(int size, _Ty unit_val = _Ty{},
                         _Operator opt = _Operator{})
        : _bit(size + 1, unit_val), _opt(opt) {}

    auto Assign(int size, _Ty unit_val) -> void {
        _bit.Assign(size, unit_val);
    }

    auto Apply(int idx, _Ty dx) -> void {
        for (int i = idx + 1; i < (int)_bit.size(); i += _Lowbit(i)) {
            _bit[i] = _opt(_bit[i], dx);
        }
    }

    auto Fill(_Ty unit_val) -> void {
        std::fill(_bit.begin(), _bit.end(), unit_val);
    }

    auto Get(int idx, _Ty res = {}) const -> _Ty {
        for (int i = idx + 1; i > 0; i -= _Lowbit(i)) {
            res = _opt(res, _bit[i]);
        }
        return res;
    }

    auto Size() const noexcept -> std::size_t {
        if (_bit.size() == 0)
            return 0;
        else
            return _bit.size() - 1;
    }

    auto operator[](int idx) -> _Ty& {
        return _bit[idx + 1];
    }

    auto operator[](int idx) const -> _Ty& {
        return _bit[idx + 1];
    }
};
