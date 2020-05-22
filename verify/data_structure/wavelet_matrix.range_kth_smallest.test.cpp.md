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


# :heavy_check_mark: data_structure/wavelet_matrix.range_kth_smallest.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/wavelet_matrix.range_kth_smallest.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-28 15:08:46+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_kth_smallest">https://judge.yosupo.jp/problem/range_kth_smallest</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/fully_indexable_dictionary.hpp.html">Fully Indexable Dictionary / 完備辞書 <small>(data_structure/fully_indexable_dictionary.hpp)</small></a>
* :heavy_check_mark: <a href="../../library/data_structure/wavelet_matrix.hpp.html">Wavelet Matrix <small>(data_structure/wavelet_matrix.hpp)</small></a>
* :heavy_check_mark: <a href="../../library/hack/fastio.hpp.html">hack/fastio.hpp</a>
* :question: <a href="../../library/utils/macros.hpp.html">utils/macros.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "data_structure/wavelet_matrix.hpp"
#include "utils/macros.hpp"
#include "hack/fastio.hpp"
#include <cstdint>
using namespace std;

int main() {
    // input
    int n = in<int>();
    int q = in<int>();
    vector<int32_t> a(n);
    REP (i, n) {
        a[i] = in<int32_t>();
    }

    // construct
    wavelet_matrix<30> wm(a);

    // output
    while (q --) {
        int l = in<int>();
        int r = in<int>();
        int k = in<int>();
        int32_t b = wm.quantile(k, l, r);
        out<int32_t>(b);
        out<char>('\n');
    }
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/wavelet_matrix.range_kth_smallest.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#line 2 "data_structure/wavelet_matrix.hpp"
#include <array>
#include <cassert>
#include <climits>
#include <cstdint>
#include <vector>
#line 2 "data_structure/fully_indexable_dictionary.hpp"
#include <algorithm>
#line 2 "utils/macros.hpp"
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))
#define REP3R(i, m, n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))
#define ALL(x) std::begin(x), std::end(x)
#line 7 "data_structure/fully_indexable_dictionary.hpp"

/**
 * @brief Fully Indexable Dictionary / 完備辞書
 * @docs data_structure/fully_indexable_dictionary.md
 * @note space complexity $o(N)$. $1.5N$-bit consumed
 */
class fully_indexable_dictionary {
    static constexpr std::size_t block_size = 64;
    std::vector<uint64_t> block;
    std::vector<int32_t> rank_block;  // a blocked cumulative sum
public:
    std::size_t size;
    fully_indexable_dictionary() = default;
    template <typename T>
    fully_indexable_dictionary(const std::vector<T> & bits) {
        size = bits.size();
        std::size_t block_count = size / block_size + 1;
        block.resize(block_count);
        REP (i, size) if (bits[i]) {
            block[i / block_size] |= (1ull << (i % block_size));
        }
        rank_block.resize(block_count);
        rank_block[0] = 0;
        REP (i, block_count - 1) {
            rank_block[i + 1] = rank_block[i] + __builtin_popcountll(block[i]);
        }
    }

    /**
     * @brief count the number of value in $[0, r)$
     * @note $O(1)$
     */
    int rank(bool value, int r) const {
        assert (0 <= r and r <= size);
        uint64_t mask = (1ull << (r % block_size)) - 1;
        int rank_1 = rank_block[r / block_size] + __builtin_popcountll(block[r /block_size] & mask);
        return value ? rank_1 : r - rank_1;
    }
    int rank(bool value, int l, int r) const {
        assert (0 <= l and l <= r and r <= size);
        return rank(value, r) - rank(value, l);
    }

    /**
     * @brief find the index of the $k$-th occurrence of value
     * @note if there is no such index, returns size
     * @note $O(\log N)$
     */
    int select(bool value, int k) const {
        if (k >= rank(value, size)) return size;
        // binary search: max { i | rank_block[i] <= k }
        int l = 0, r = block.size();  // [l, r)
        while (r - l > 1) {
            int m = (l + r) / 2;
            int rank_block_m = (value ? rank_block[m] : m * block_size - rank_block[m]);
            (rank_block_m <= k ? l : r) = m;
        }
        int block_index = l;
        // binary search: max { i | rank(i) <= k }
        l = block_index * block_size;
        r = std::min<int>(size, (block_index + 1) * block_size);  // [l, r)
        while (r - l > 1) {
            int m = (l + r) / 2;
            (rank(value, m) <= k ? l : r) = m;
        }
        return l;
    }
    /**
     * @brief select(value, k) in [l, size)
     */
    int select(bool value, int k, int l) const {
        assert (0 <= l and l <= size);
        return select(value, k + rank(value, l));
    }

    /**
     * @brief get the $i$-th element
     * @note $O(1)$
     */
    bool access(int i) const {
        assert (0 <= i and i < size);
        return block[i / block_size] & (1ull << (i % block_size));
    }
};
#line 9 "data_structure/wavelet_matrix.hpp"


/**
 * @brief Wavelet Matrix
 * @docs data_structure/wavelet_matrix.md
 * @tparam BITS express the range [0, 2^BITS) of values. You can assume BITS \le \log N, using coordinate compression
 * @see https://www.slideshare.net/pfi/ss-15916040
 */
template <int BITS>
struct wavelet_matrix {
    static_assert (BITS < CHAR_BIT * sizeof(uint64_t), "");
    std::array<fully_indexable_dictionary, BITS> fid;
    std::array<int, BITS> zero_count;

    wavelet_matrix() = default;
    /**
     * @note O(N BITS)
     */
    template <typename T>
    wavelet_matrix(std::vector<T> data) {
        int size = data.size();
        REP (i, size) {
            assert (0 <= data[i] and data[i] < (1ull << BITS));
        }
        // bit-inversed radix sort
        std::vector<char> bits(size);
        std::vector<T> next(size);
        REP_R (k, BITS) {
            auto low  = next.begin();
            auto high = next.rbegin();
            REP (i, size) {
                bits[i] = bool(data[i] & (1ull << k));
                (bits[i] ? *(high ++) : *(low ++)) = data[i];
            }
            fid[k] = fully_indexable_dictionary(bits);
            zero_count[k] = low - next.begin();
            reverse(next.rbegin(), high);
            data.swap(next);
        }
    }

    /**
     * @brief count the occurrences of value in [l, r)
     * @note O(BITS)
     * @note even if l = 0, of course the final [l, r) is not always [0, r)
     */
    int rank(uint64_t value, int l, int r) const {
        assert (0 <= value and value < (1ull << BITS));
        assert (0 <= l and l <= r and r <= fid[0].size);
        REP_R (k, BITS) {
            bool p = value & (1ull << k);
            l = fid[k].rank(p, l) + p * zero_count[k];
            r = fid[k].rank(p, r) + p * zero_count[k];
        }
        return r - l;
    }
    int rank(uint64_t value, int r) const {
        return rank(value, 0, r);
    }

    /**
     * @brief find the index of the k-th occurence of value
     * @note O(BITS SELECT) when FID's select() is O(SELECT)
     */
    int select(uint64_t value, int k) const {
        assert (0 <= value and value < (1ull << BITS));
        assert (0 <= k);
        // do rank(value, 0, size) with logging
        std::vector<int> l(BITS + 1), r(BITS + 1);
        l[BITS] = 0;
        r[BITS] = fid[0].size;
        REP_R (d, BITS) {
            bool p = value & (1ull << d);
            l[d] = fid[d].rank(p, l[d + 1]) + p * zero_count[d];
            r[d] = fid[d].rank(p, r[d + 1]) + p * zero_count[d];
        }
        if (r[0] - l[0] <= k) return fid[0].size;
        // trace the log inversely
        REP (d, BITS) {
            bool p = value & (1ull << d);
            k = fid[d].select(p, k, l[d + 1]) - l[d + 1];
        }
        return k;
    }
    /**
     * @brief find the index of the k-th occurence of value in [l, n)
     */
    int select(uint64_t value, int k, int l) const {
        return select(value, k + rank(value, l));
    }

    /**
     * @brief returns the i-th element
     * @note O(BITS)
     */
    uint64_t access(int i) const {
        assert (0 <= i and i < fid[0].size);
        uint64_t acc = 0;
        REP_R (k, BITS) {
            bool p = fid[k].access(i);
            acc |= uint64_t(p) << k;
            i = fid[k].rank(p, i) + p * zero_count[k];
        }
        return acc;
    }

    /**
     * @brief find the k-th number in [l, r)
     * @note O(BITS)
     */
    uint64_t quantile(int k, int l, int r) {
        assert (0 <= k);
        assert (0 <= l and l <= r and r <= fid[0].size);
        if (r - l <= k) return 1ull << BITS;
        uint64_t acc = 0;
        REP_R (d, BITS) {
            int lc = fid[d].rank(1, l);
            int rc = fid[d].rank(1, r);
            int zero = (r - l) - (rc - lc);
            bool p = (k >= zero);
            if (p) {
                acc |= 1ull << d;
                l = lc + zero_count[d];
                r = rc + zero_count[d];
                k -= zero;
            } else {
                l -= lc;
                r -= rc;
            }
        }
        return acc;
    }

    /**
     * @brief count the number of values in [value_l, value_r) in range [l, r)
     * @note O(BITS)
     */
    int range_frequency(int l, int r, uint64_t value_l, uint64_t value_r) const {
        assert (0 <= l and l <= r and r <= fid[0].size);
        assert (0 <= value_l and value_l <= value_r and value_r <= (1ull << BITS));
        return range_frequency(BITS - 1, l, r, 0, value_l, value_r);
    }
    int range_frequency(int k, int l, int r, uint64_t v, uint64_t a, uint64_t b) const {
        if (l == r) return 0;
        if (k == -1) return (a <= v and v < b) ? r - l : 0;
        uint64_t nv  =  v |  (1ull << k);
        uint64_t nnv = nv | ((1ull << k) - 1);
        if (nnv < a or b <= v) return 0;
        if (a <= v and nnv < b) return r - l;
        int lc = fid[k].rank(1, l);
        int rc = fid[k].rank(1, r);
        return
            range_frequency(k - 1,             l - lc,             r - rc,  v, a, b) +
            range_frequency(k - 1, lc + zero_count[k], rc + zero_count[k], nv, a, b);
    }

    /**
     * @brief flexible version of range_frequency, buf a little bit slow
     * @note O(K BITS), K is the number of kinds of values in the range
     * @arg void callback(uint64_t value, int count)
     */
    template <typename Func>
    void range_frequency_callback(int l, int r, uint64_t value_l, uint64_t value_r, Func callback) const {
        assert (0 <= l and l <= r and r <= fid[0].size);
        assert (0 <= value_l and value_l <= value_r and value_r <= (1ull << BITS));
        range_frequency_callback(BITS - 1, l, r, 0, value_l, value_r, callback);
    }
    template <typename Func>
    void range_frequency_callback(int k, int l, int r, uint64_t v, uint64_t a, uint64_t b, Func callback) const {
        if (l == r) return;
        if (b <= v) return;
        if (k == -1) {
            if (a <= v) callback(v, r - l);
            return;
        }
        uint64_t nv  = v  | (1ull << k);
        uint64_t nnv = nv | (((1ull << k) - 1));
        if (nnv < a) return;
        int lc = fid[k].rank(1, l);
        int rc = fid[k].rank(1, r);
        range_frequency_callback(k - 1,             l - lc,             r - rc,  v, a, b, callback);
        range_frequency_callback(k - 1, lc + zero_count[k], rc + zero_count[k], nv, a, b, callback);
    }
};
#line 3 "hack/fastio.hpp"
#include <cstdio>
#include <string>
#include <type_traits>

template <class Char, std::enable_if_t<std::is_same_v<Char, char>, int> = 0>
inline Char in() { return getchar_unlocked(); }
template <class String, std::enable_if_t<std::is_same_v<String, std::string>, int> = 0>
inline std::string in() {
    char c; do { c = getchar_unlocked(); } while (isspace(c));
    std::string s;
    do { s.push_back(c); } while (not isspace(c = getchar_unlocked()));
    return s;
}
template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
inline Integer in() {
    char c; do { c = getchar_unlocked(); } while (isspace(c));
    if (std::is_signed<Integer>::value and c == '-') return -in<Integer>();
    Integer n = 0;
    do { n = n * 10 + c - '0'; } while (not isspace(c = getchar_unlocked()));
    return n;
}

template <class Char, std::enable_if_t<std::is_same_v<Char, char>, int> = 0>
inline void out(char c) { putchar_unlocked(c); }
template <class String, std::enable_if_t<std::is_same_v<String, std::string>, int> = 0>
inline void out(const std::string & s) { for (char c : s) putchar_unlocked(c); }
template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
inline void out(Integer n) {
    char s[20];
    int i = 0;
    if (std::is_signed<Integer>::value and n < 0) { putchar_unlocked('-'); n *= -1; }
    do { s[i ++] = n % 10; n /= 10; } while (n);
    while (i) putchar_unlocked(s[-- i] + '0');
}
#line 6 "data_structure/wavelet_matrix.range_kth_smallest.test.cpp"
using namespace std;

int main() {
    // input
    int n = in<int>();
    int q = in<int>();
    vector<int32_t> a(n);
    REP (i, n) {
        a[i] = in<int32_t>();
    }

    // construct
    wavelet_matrix<30> wm(a);

    // output
    while (q --) {
        int l = in<int>();
        int r = in<int>();
        int k = in<int>();
        int32_t b = wm.quantile(k, l, r);
        out<int32_t>(b);
        out<char>('\n');
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

