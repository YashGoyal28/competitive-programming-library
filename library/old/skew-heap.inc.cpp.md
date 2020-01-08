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


# :warning: old/skew-heap.inc.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/skew-heap.inc.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-08 18:35:19+09:00


* see: <a href="http://hos.ac/blog/#blog0001">http://hos.ac/blog/#blog0001</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @sa http://hos.ac/blog/#blog0001
 */
template <class T>
class skew_heap {
    struct node_t {
        node_t *left, *right;
        T value;
    };
    static node_t *merge(node_t *a, node_t *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->value > b->value) swap(a, b);
        a->right = merge(a->right, b);
        swap(a->left, a->right);
        return a;
    }
    static void release(node_t *node) {
        if (node == nullptr) return;
        release(node->left);
        release(node->right);
        delete node;
    }
    node_t *root;
public:
    skew_heap() : root(nullptr) {}
    ~ skew_heap() { release(root); }
    void push(T a) {
        node_t *node = new node_t;
        node->left = node->right = nullptr;
        node->value = a;
        root = merge(root, node);
    }
    T get_min() {
        assert (root != nullptr);
        return root->value;
    }
    void pop() {
        assert (root != nullptr);
        node_t *node = merge(root->left, root->right);
        delete root;
        root = node;
    }
    bool empty() {
        return root == nullptr;
    }
    void merge(skew_heap & other) {
        root = skew_heap::merge(root, other.root);
        other.root = nullptr;
    }
};

unittest {
    default_random_engine gen;
    skew_heap<int> skew;
    priority_queue<int, vector<int>, greater<int> > que;
    REP (iteration, 100000) {
        if (que.empty() or bernoulli_distribution(0.5)(gen)) {
            int k = uniform_int_distribution<int>(1, 100)(gen);
            skew_heap<int> skew1;
            while (k --) {
                int a = uniform_int_distribution<int>()(gen);
                skew1.push(a);
                que.push(a);
            }
            skew.merge(skew1);
            assert (skew1.empty());
        } else {
            int a = skew.get_min();
            int b = que.top();
            assert (a == b);
            skew.pop();
            que.pop();
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/skew-heap.inc.cpp"
/**
 * @sa http://hos.ac/blog/#blog0001
 */
template <class T>
class skew_heap {
    struct node_t {
        node_t *left, *right;
        T value;
    };
    static node_t *merge(node_t *a, node_t *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->value > b->value) swap(a, b);
        a->right = merge(a->right, b);
        swap(a->left, a->right);
        return a;
    }
    static void release(node_t *node) {
        if (node == nullptr) return;
        release(node->left);
        release(node->right);
        delete node;
    }
    node_t *root;
public:
    skew_heap() : root(nullptr) {}
    ~ skew_heap() { release(root); }
    void push(T a) {
        node_t *node = new node_t;
        node->left = node->right = nullptr;
        node->value = a;
        root = merge(root, node);
    }
    T get_min() {
        assert (root != nullptr);
        return root->value;
    }
    void pop() {
        assert (root != nullptr);
        node_t *node = merge(root->left, root->right);
        delete root;
        root = node;
    }
    bool empty() {
        return root == nullptr;
    }
    void merge(skew_heap & other) {
        root = skew_heap::merge(root, other.root);
        other.root = nullptr;
    }
};

unittest {
    default_random_engine gen;
    skew_heap<int> skew;
    priority_queue<int, vector<int>, greater<int> > que;
    REP (iteration, 100000) {
        if (que.empty() or bernoulli_distribution(0.5)(gen)) {
            int k = uniform_int_distribution<int>(1, 100)(gen);
            skew_heap<int> skew1;
            while (k --) {
                int a = uniform_int_distribution<int>()(gen);
                skew1.push(a);
                que.push(a);
            }
            skew.merge(skew1);
            assert (skew1.empty());
        } else {
            int a = skew.get_min();
            int b = que.top();
            assert (a == b);
            skew.pop();
            que.pop();
        }
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

