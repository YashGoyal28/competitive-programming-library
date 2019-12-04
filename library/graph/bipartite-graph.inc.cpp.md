<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: graph/bipartite-graph.inc.cpp
* category: graph


[Back to top page](../../index.html)



## Code
```cpp
/**
 * @note g must be connected
 * @return is the size of a part
 */
int check_bipartite_graph(vector<vector<int> > const & g) {
    int n = g.size();
    vector<char> used(n, -1);
    function<bool (int, int)> dfs = [&](int i, int parent) {
        for (int j : g[i]) {
            if (used[j] != -1) {
                if (used[j] == used[i]) {
                    return false;
                }
            } else {
                used[j] = used[i] ^ 1;
                if (not dfs(j, i)) return false;
            }
        }
        return true;
    };
    used[0] = 0;
    if (not dfs(0, -1)) return -1;
    return count(whole(used), 0);
}

```

[Back to top page](../../index.html)
