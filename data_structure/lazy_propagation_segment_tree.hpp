#pragma once
#include <algorithm>
#include <cassert>
#include <vector>
#include "utils/macros.hpp"

/**
 * @note lazy_propagation_segment_tree<max_monoid, plus_operator_monoid> is the starry sky tree
 * @note verified https://www.hackerrank.com/contests/world-codesprint-12/challenges/factorial-array/submissions/code/1304452669
 * @note verified https://www.hackerrank.com/contests/world-codesprint-12/challenges/animal-transport/submissions/code/1304454860
 * @note intersting discussion about range-extension and partial-function-extension: https://github.com/kmyk/competitive-programming-library/issues/3
 */
template <class Monoid, class OperatorMonoid>
struct lazy_propagation_segment_tree { // on monoids
    static_assert (std::is_same<typename Monoid::underlying_type, typename OperatorMonoid::target_type>::value, "");
    typedef typename Monoid::underlying_type underlying_type;
    typedef typename OperatorMonoid::underlying_type operator_type;
    const Monoid mon;
    const OperatorMonoid op;
    int n;
    std::vector<underlying_type> a;
    std::vector<operator_type> f;
    lazy_propagation_segment_tree() = default;
    lazy_propagation_segment_tree(int a_n, underlying_type initial_value = Monoid().unit(), Monoid const & a_mon = Monoid(), OperatorMonoid const & a_op = OperatorMonoid())
            : mon(a_mon), op(a_op) {
        n = 1; while (n <= a_n) n *= 2;
        a.resize(2 * n - 1, mon.unit());
        std::fill(a.begin() + (n - 1), a.begin() + ((n - 1) + a_n), initial_value); // set initial values
        REP_R (i, n - 1) a[i] = mon.append(a[2 * i + 1], a[2 * i + 2]); // propagate initial values
        f.resize(std::max(0, (2 * n - 1) - n), op.identity());
    }
    void point_set(int i, underlying_type z) {
        assert (0 <= i and i < n);
        point_set(0, 0, n, i, z);
    }
    void point_set(int i, int il, int ir, int j, underlying_type z) {
        if (i == n + j - 1) { // 0-based
            a[i] = z;
        } else if (ir <= j or j+1 <= il) {
            // nop
        } else {
            range_apply(2 * i + 1, il, (il + ir) / 2, 0, n, f[i]);
            range_apply(2 * i + 2, (il + ir) / 2, ir, 0, n, f[i]);
            f[i] = op.identity();
            point_set(2 * i + 1, il, (il + ir) / 2, j, z);
            point_set(2 * i + 2, (il + ir) / 2, ir, j, z);
            a[i] = mon.append(a[2 * i + 1], a[2 * i + 2]);
        }
    }
    void range_apply(int l, int r, operator_type z) {
        assert (0 <= l and l <= r and r <= n);
        range_apply(0, 0, n, l, r, z);
    }
    void range_apply(int i, int il, int ir, int l, int r, operator_type z) {
        if (l <= il and ir <= r) { // 0-based
            a[i] = op.apply(z, a[i]);
            if (i < f.size()) f[i] = op.compose(z, f[i]);
        } else if (ir <= l or r <= il) {
            // nop
        } else {
            range_apply(2 * i + 1, il, (il + ir) / 2, 0, n, f[i]);
            range_apply(2 * i + 2, (il + ir) / 2, ir, 0, n, f[i]);
            f[i] = op.identity();  // unnecessary if the oprator monoid is commutative
            range_apply(2 * i + 1, il, (il + ir) / 2, l, r, z);
            range_apply(2 * i + 2, (il + ir) / 2, ir, l, r, z);
            a[i] = mon.append(a[2 * i + 1], a[2 * i + 2]);
        }
    }
    underlying_type range_concat(int l, int r) {
        assert (0 <= l and l <= r and r <= n);
        underlying_type lacc = mon.unit(), racc = mon.unit();
        for (int l1 = (l += n), r1 = (r += n) - 1; l1 > 1; l /= 2, r /= 2, l1 /= 2, r1 /= 2) { // 1-based loop, 2x faster than recursion
            if (l < r) {
                if (l % 2 == 1) lacc = mon.append(lacc, a[(l ++) - 1]);
                if (r % 2 == 1) racc = mon.append(a[(-- r) - 1], racc);
            }
            lacc = op.apply(f[l1 / 2 - 1], lacc);
            racc = op.apply(f[r1 / 2 - 1], racc);
        }
        return mon.append(lacc, racc);
    }
};


#include <array>
#include <climits>
#include <utility>
#include "modulus/mint.hpp"

struct max_monoid {
    typedef int underlying_type;
    int unit() const { return 0; }
    int append(int a, int b) const { return std::max(a, b); }
};
struct plus_operator_monoid {
    typedef int underlying_type;
    typedef int target_type;
    int identity() const { return 0; }
    int apply(underlying_type a, target_type b) const { return a + b; }
    int compose(underlying_type a, underlying_type b) const { return a + b; }
};
typedef lazy_propagation_segment_tree<max_monoid, plus_operator_monoid> starry_sky_tree;

struct min_monoid {
    typedef int underlying_type;
    int unit() const { return INT_MAX; }
    int append(int a, int b) const { return std::min(a, b); }
};
struct plus_with_int_max_operator_monoid {
    typedef int underlying_type;
    typedef int target_type;
    int identity() const { return 0; }
    int apply(underlying_type a, target_type b) const { return b == INT_MAX ? INT_MAX : a + b; }
    int compose(underlying_type a, underlying_type b) const { return a + b; }
};

template <int N>
struct count_monoid {
    typedef std::array<int, N> underlying_type;
    underlying_type unit() const { return underlying_type(); }
    underlying_type append(underlying_type a, underlying_type b) const {
        underlying_type c = {};
        REP (i, N) c[i] = a[i] + b[i];
        return c;
    }
};
template <int N>
struct increment_operator_monoid {
    typedef int underlying_type;
    typedef std::array<int, N> target_type;
    underlying_type identity() const { return 0; }
    target_type apply(underlying_type a, target_type b) const {
        if (a == 0) return b;
        target_type c = {};
        REP (i, N - a) c[i + a] = b[i];
        return c;
    }
    underlying_type compose(underlying_type a, underlying_type b) const { return a + b; }
};

template <int32_t MOD>
struct modplus_length_monoid {
    typedef std::pair<mint<MOD>, int> underlying_type;
    underlying_type unit() const { return std::make_pair(0, 0); }
    underlying_type append(underlying_type a, underlying_type b) const { return std::make_pair(a.first + b.first, a.second + b.second); }
    static underlying_type make(mint<MOD> a) { return std::make_pair(a, 1); }
};
template <int32_t MOD>
struct modular_linear_operator_monoid {
    typedef std::pair<mint<MOD>, mint<MOD> > underlying_type;
    typedef std::pair<mint<MOD>, int> target_type;
    static underlying_type make(mint<MOD> a, mint<MOD> b) {
        return std::make_pair(a, b);
    }
    underlying_type identity() const {
        return make(1, 0);
    }
    target_type apply(underlying_type a, target_type b) const {
        return std::make_pair(a.first * b.first + a.second * b.second, b.second);
    }
    underlying_type compose(underlying_type a, underlying_type b) const {
        return make(a.first * b.first, a.second + a.first * b.second);
    }
};
