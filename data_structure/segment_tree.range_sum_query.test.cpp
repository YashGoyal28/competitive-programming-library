#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include "data_structure/segment_tree.hpp"
#include "utils/monoids.hpp"

#include <iostream>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    segment_tree<plus_monoid<int> > segtree(n);
    while (q --) {
        int com, x, y; cin >> com >> x >> y;
        -- x;
        if (com == 0) {
            segtree.point_set(x, segtree.range_concat(x, x + 1) + y);
        } else if (com == 1) {
            cout << segtree.range_concat(x, y) << endl;
        }
    }
    return 0;
}