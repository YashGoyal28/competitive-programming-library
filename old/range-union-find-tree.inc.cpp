/**
 * @note 計算量は確かに落ちるのだけどこれを使って速くなるケースは元々全部連結してて自明な気がする
 * @note thank to https://beta.atcoder.jp/contests/yahoo-procon2018-final/submissions/2126707
 */
struct range_union_find_tree {
    vector<union_find_tree> data;
    range_union_find_tree() = default;
    explicit range_union_find_tree(size_t n) {
        int log_n = 32 - __builtin_clz(n);
        data.resize(log_n, union_find_tree(n));
    }
    /**
     * @description unite (l1 + k)-th tree and (l2 + k)-th tree for each k in [0, len)
     * @note O(1)
     */
    void range_unite_trees(int l1, int l2, int len) {
        int n = data.front().data.size();
        assert (0 <= l1 and l1 + len <= n);
        assert (0 <= l2 and l2 + len <= n);
        assert (len >= 1);
        int k = 31 - __builtin_clz(len);  // log2
        data[k].unite_trees(l1, l2);
        data[k].unite_trees(l1 + len - (1 << k), l2 + len - (1 << k));
    }
    /**
     * @description collapse range-queries and get result
     * @note O(N \log N)
     */
    union_find_tree const & update() {
        int n = data.front().data.size();
        int log_n = data.size();
        REP_R (k, log_n - 1) {
            REP (i, n - (1 << k)) {
                int root = data[k + 1].find_root(i);
                data[k].unite_trees(i, root);
                data[k].unite_trees(i + (1 << k), root + (1 << k));
            }
        }
        return data[0];
    }
};
