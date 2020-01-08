// http://sigma425.hatenablog.com/entry/2015/12/25/224053
vector<int> dominator_tree(vector<vector<int> > const & g, int root_g) { // G is a digraph which any vertex can be reached from the root
    int n = g.size();
    vector<vector<int> > invert_g(n);
    repeat (i,n) for (int j : g[i]) invert_g[j].push_back(i);
    // 1. make dfs tree
    vector<int> to_rank(n, -1); // index on original digraph G -> index on dfs-tree T
    vector<int> from_rank(n);
    vector<int> parent(n, -1); // on dfs-tree T, indexed on G
    { // init
        int next_rank = 0;
        function<void (int)> dfs = [&](int i) {
            to_rank[i] = next_rank;
            from_rank[next_rank] = i;
            ++ next_rank;
            for (int j : g[i]) if (to_rank[j] == -1) {
                parent[j] = i;
                dfs(j);
            }
        };
        dfs(root_g);
    }
    // x. check connectivity
    repeat (i,n) assert (to_rank[i] != -1); // or disconnected graph
    // 2. compute sdom
    vector<int> sdom(n);
    repeat (i,n) sdom[i] = to_rank[i];
    vector<int> foo(n, -1); // vertex, used in 3.
    // 2.1. union-find tree
    vector<int> root(n); whole(iota, root, 0);
    vector<int> min_sdom_index(n); whole(iota, min_sdom_index, 0); // data on union-find tree
    function<int (int)> find = [&](int i) {
        if (root[i] == i) return i;
        int j = find(root[i]);
        if (sdom[min_sdom_index[root[i]]] < sdom[min_sdom_index[i]]) {
            min_sdom_index[i] = min_sdom_index[root[i]];
        }
        return root[i] = j;
    };
    auto link = [&](int i, int j) {
        assert (root[j] == j);
        root[j] = i;
    };
    vector<vector<int> > bucket(n);
    for (int rank_i = n-1; rank_i >= 1; -- rank_i) {
        // 2.2. compute sdom
        int i = from_rank[rank_i];
        for (int j : invert_g[i]) {
            // int rank_j = to_rank[j];
            // if (rank_j < rank_i) { // up
            //     setmin(sdom[i], rank_j);
            // }
            find(j);
            setmin(sdom[i], sdom[min_sdom_index[j]]);
        }
        // 2.3. compute foo
        bucket[from_rank[sdom[i]]].push_back(i);
        for (int j : bucket[parent[i]]) {
            find(j);
            foo[j] = min_sdom_index[j];
        }
        bucket[parent[i]] = vector<int>(); // clear
        // 2.4. link
        link(parent[i], i);
    }
    // 3. compute idom
    vector<int> idom(n);
    repeat_from (rank_i,1,n) {
        int i = from_rank[rank_i];
        int j = foo[i];
        idom[i] = (sdom[i] == sdom[j] ? sdom : idom)[j];
    }
    vector<int> result(n);
    repeat (i,n) if (i != root_g) {
        result[i] = from_rank[idom[i]];
    }
    result[root_g] = -1;
    return result;
}
