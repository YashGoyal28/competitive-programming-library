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


# :warning: number/primes.hpp
* category: number


[Back to top page](../../index.html)



## Dependencies
* :heavy_check_mark: [utils/macros.hpp](../utils/macros.hpp.html)


## Required
* :warning: [utils/fast_zeta_transform.hpp](../utils/fast_zeta_transform.hpp.html)


## Verified
* :heavy_check_mark: [number/primes.aoj.test.cpp](../../verify/number/primes.aoj.test.cpp.html)


## Code
```cpp
#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <map>
#include <vector>
#include "utils/macros.hpp"

/**
 * @note O(\sqrt{n})
 */
struct prepared_primes {
    int size;
    std::vector<int> sieve;
    std::vector<int> primes;

    prepared_primes(int size_)
        : size(size_) {

        sieve.resize(size);
        REP3 (p, 2, size) if (sieve[p] == 0) {
            primes.push_back(p);
            for (int k = p; k < size; k += p) {
                if (sieve[k] == 0) {
                    sieve[k] = p;
                }
            }
        }
    }

    std::vector<int64_t> list_prime_factors(int64_t n) {
        assert (1 <= n and n < (int64_t)size * size);
        std::vector<int64_t> result;

        // trial division for large part
        for (int p : primes) {
            if (n < size or n < (int64_t)p * p) {
                break;
            }
            while (n % p == 0) {
                n /= p;
                result.push_back(p);
            }
        }

        // small part
        if (n == 1) {
            // nop
        } else if (n < size) {
            while (n != 1) {
                result.push_back(sieve[n]);
                n /= sieve[n];
            }
        } else {
            result.push_back(n);
        }

        assert (std::is_sorted(ALL(result)));
        return result;
    }

    bool is_prime(int64_t n) {
        return list_prime_factors(n).size() == 1;
    }

    std::vector<int64_t> list_all_factors(int64_t n) {
        auto p = list_prime_factors(n);
        std::vector<int64_t> d;
        d.push_back(1);
        for (int l = 0; l < p.size(); ) {
            int r = l + 1;
            while (r < p.size() and p[r] == p[l]) ++ r;
            int n = d.size();
            REP (k1, r - l) {
                REP (k2, n) {
                    d.push_back(d[d.size() - n] * p[l]);
                }
            }
            l = r;
        }
        return d;
    }

    std::map<int64_t, int> list_prime_factors_as_map(int64_t n) {
        std::map<int64_t, int> cnt;
        for (int64_t p : list_prime_factors(n)) {
            ++ cnt[p];
        }
        return cnt;
    }

    int64_t euler_totient(int64_t n) {
        int64_t phi = 1;
        int64_t last = -1;
        for (int64_t p : list_prime_factors(n)) {
            if (last != p) {
                last = p;
                phi *= p - 1;
            } else {
                phi *= p;
            }
        }
        return phi;
    }
};

```

[Back to top page](../../index.html)
