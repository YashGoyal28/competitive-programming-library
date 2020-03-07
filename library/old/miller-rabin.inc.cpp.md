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


# VerificationStatus.DEFAULT old/miller-rabin.inc.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/miller-rabin.inc.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-08 18:35:19+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// https://kimiyuki.net/blog/2016/02/01/cf-gym-100753/
template <class Generator>
bool is_prime(ll n, int iteration, Generator & gen) { // miller-rabin primality test, O(k log n)
    assert (0 <= n);
    if (n == 2) return true;
    if (n == 1 or n % 2 == 0) return false;
    const ll d = (n-1) >> __builtin_ctzll(n-1); // remove trailing zeros
    uniform_int_distribution<ll> dist(1, n-2); // [l, r]
    repeat (dummy, iteration) {
        ll a = dist(gen);
        ll t = d;
        ll y = powmod(a, t, n);
        while (t != n-1 and y != 1 and y != n-1) {
            y = y * y % n;
            t *= 2;
        }
        if (y != n-1 and t % 2 == 0) return false;
    }
    return true;
}
bool is_prime(ll n) {
    static default_random_engine engine = default_random_engine(random_device()());
    return is_prime(n, 20, engine);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/miller-rabin.inc.cpp"
// https://kimiyuki.net/blog/2016/02/01/cf-gym-100753/
template <class Generator>
bool is_prime(ll n, int iteration, Generator & gen) { // miller-rabin primality test, O(k log n)
    assert (0 <= n);
    if (n == 2) return true;
    if (n == 1 or n % 2 == 0) return false;
    const ll d = (n-1) >> __builtin_ctzll(n-1); // remove trailing zeros
    uniform_int_distribution<ll> dist(1, n-2); // [l, r]
    repeat (dummy, iteration) {
        ll a = dist(gen);
        ll t = d;
        ll y = powmod(a, t, n);
        while (t != n-1 and y != 1 and y != n-1) {
            y = y * y % n;
            t *= 2;
        }
        if (y != n-1 and t % 2 == 0) return false;
    }
    return true;
}
bool is_prime(ll n) {
    static default_random_engine engine = default_random_engine(random_device()());
    return is_prime(n, 20, engine);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

