#include <bits/stdc++.h>
using namespace std;

template <typename Key, typename Value>
struct CartesianTree {
    struct Node {
        Node(int lc = -1, int rc = -1) : key(), value(), lc(lc), rc(rc) {}
        Node(Key key, Value value, int lc = -1, int rc = -1)
            : key(std::move(key)), value(std::move(value)), lc(lc), rc(rc) {}
        Key key;
        Value value;
        int lc, rc;
    };
    std::vector<Node> tr;
    int root;

    void Build(auto key_cmp, auto val_cmp /* less */) {
        std::ranges::stable_sort(tr, key_cmp, &Node::val);
        std::vector<int> stk(tr.size());
        int top = 0;
        for (int i = 0; i < tr.size(); i ++) {
            int k = top - 1;
            while (k >= 0 && val_cmp(tr[i].value, tr[stk[k]].value)) {
                k --;
            }
            if (k >= 0) {
                tr[stk[k]].lc = i;
            }
            if (k + 1 < top) {
                tr[i].rc = stk[k + 1];
            }
            stk[++ k] = i;
            top = k + 1;
        }
        root = stk[0];
    }
};