template <int32_t MOD>
mint<MOD> fact(int n) {
    static vector<mint<MOD> > memo(1, 1);
    while (n >= memo.size()) {
        memo.push_back(memo.back() * mint<MOD>(memo.size()));
    }
    return memo[n];
}
template <int32_t PRIME>
mint<PRIME> inv_fact(int n) {
    static vector<mint<PRIME> > memo(1, 1);
    while (n >= memo.size()) {
        memo.push_back(memo.back() * mint<PRIME>(memo.size()).inv());
    }
    return memo[n];
}

unittest {
    constexpr int32_t MOD = 1e9 + 7;
    assert (fact<MOD>(0) == 1);
    assert (fact<MOD>(1) == 1);
    assert (fact<MOD>(2) == 2);
    assert (fact<MOD>(3) == 6);
    assert (fact<MOD>(4) == 24);
    assert (fact<MOD>(5) == 120);
}
