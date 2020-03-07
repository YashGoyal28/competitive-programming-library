---
layout: default
---

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


# VerificationStatus.DEFAULT old/trie-tree.inc.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/trie-tree.inc.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-08 18:35:19+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct trie_t {
    T data;
    array<shared_ptr<trie_t>, 26> children;
};
template <typename T>
shared_ptr<trie_t<T> > trie_insert(shared_ptr<trie_t<T> > original_t, string const & s, T data) {
    if (not original_t) original_t = make_shared<trie_t<T> >();
    auto t = original_t;
    for (char c : s) {
        assert (isalpha(c));
        int i = toupper(c) - 'A';
        if (not t->children[i]) t->children[i] = make_shared<trie_t<T> >();
        t = t->children[i];
    }
    t->data = data;
    return original_t;
}
template <typename T>
shared_ptr<trie_t<T> > trie_find(shared_ptr<trie_t<T> > const & t, string const & s, int i) {
    if (t == nullptr) return t;
    if (i == s.length()) return t;
    char c = s[i];
    int j = toupper(c) - 'A';
    return trie_find(t->children[j], s, i + 1);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/trie-tree.inc.cpp"
template <typename T>
struct trie_t {
    T data;
    array<shared_ptr<trie_t>, 26> children;
};
template <typename T>
shared_ptr<trie_t<T> > trie_insert(shared_ptr<trie_t<T> > original_t, string const & s, T data) {
    if (not original_t) original_t = make_shared<trie_t<T> >();
    auto t = original_t;
    for (char c : s) {
        assert (isalpha(c));
        int i = toupper(c) - 'A';
        if (not t->children[i]) t->children[i] = make_shared<trie_t<T> >();
        t = t->children[i];
    }
    t->data = data;
    return original_t;
}
template <typename T>
shared_ptr<trie_t<T> > trie_find(shared_ptr<trie_t<T> > const & t, string const & s, int i) {
    if (t == nullptr) return t;
    if (i == s.length()) return t;
    char c = s[i];
    int j = toupper(c) - 'A';
    return trie_find(t->children[j], s, i + 1);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

