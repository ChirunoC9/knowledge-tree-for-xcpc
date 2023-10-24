#include <bits/stdc++.h>

using namespace std;

int main() {
    array<array<int, 4>, 4> mat = {{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
    }};

    auto Rotate = [](auto &&mat) {
        remove_reference_t<decltype(mat)> ret;
        for (int i = 0; i < mat.size(); i += 1) {
            for (int j = 0; j < mat[i].size(); j += 1) {
                ret[mat.size() - i - 1][j] = mat[j][i];
            }
        }
        return ret;
    };
    auto ret = Rotate(mat);

    for (auto i : ret) {
        for (auto j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}
