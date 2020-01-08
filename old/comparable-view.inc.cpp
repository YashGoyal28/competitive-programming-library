/**
 * @brief compare substrings of a string with O(1) using suffix arrays
 * @note O(1)
 */
int string_view_strcmp(int l1, int r1, int l2, int r2, vector<int> const & rank, sparse_table<min_semilattice> const & lcp) {
    int rank_l, rank_r; tie(rank_l, rank_r) = minmax({ rank[l1], rank[l2] });
    int k = lcp.range_concat(rank_l, rank_r);
    if (min(r1 - l1, r2 - l2) <= k) {
        return (r1 - l1) - (r2 - l2);
    } else {
        return rank[l1] - rank[l2];
    }
}

unittest {
    default_random_engine gen;
    REP (iteration, 100) {
        int length = uniform_int_distribution<int>(10, 100)(gen);
        string s;
        REP (i, length) {
            s += uniform_int_distribution<char>('A', 'Z')(gen);
        }
        vector<int> sa, rank;
        suffix_array(s, sa, rank);
        vector<int> lcp_ = longest_common_prefix_array(s, sa, rank);
        sparse_table<min_semilattice> lcp = sparse_table<min_semilattice>(lcp_);
        REP (iteration, 100) {
            int l1 = uniform_int_distribution<int>(0, length / 2)(gen);
            int r1 = uniform_int_distribution<int>(l1, length)(gen);
            int l2 = uniform_int_distribution<int>(0, length / 2)(gen);
            int r2 = uniform_int_distribution<int>(l2, length)(gen);
            auto sub1 = s.substr(l1, r1 - l1);
            auto sub2 = s.substr(l2, r2 - l2);
            assert ((string_view_strcmp(l1, r1, l2, r2, rank, lcp) < 0) == (sub1 < sub2));
        }
    }
}

/**
 * @brief as a class
 */
class comparable_string_view_factory {
public:
    class comparable_string_view {
    public:
        const comparable_string_view_factory *factory;
        const int l, r;
    private:
        friend class comparable_string_view_factory;
        comparable_string_view(const comparable_string_view_factory *factory_, int l_, int r_)
                : factory(factory_), l(l_), r(r_) {
        }
    public:
        inline bool empty() const { return r == 0; }
        inline size_t size() const { return r - l; }
        inline char operator [] (size_t i) const {
            assert (0 <= i and i < size());
            return factory->s[l + i];
        }
        inline bool operator < (comparable_string_view const & other) const {
            assert (this->factory == other.factory);
            return this->factory->strcmp(this->l, this->r, other.l, other.r) < 0;
        }
        inline bool operator == (comparable_string_view const & other) const {
            assert (this->factory == other.factory);
            return this->factory->strcmp(this->l, this->r, other.l, other.r) == 0;
        }
        inline bool operator != (comparable_string_view const & other) const {
            assert (this->factory == other.factory);
            return this->factory->strcmp(this->l, this->r, other.l, other.r) != 0;
        }
    };
private:
    string s;
    vector<int> sa, rank;
    sparse_table<min_semilattice> lcp;
public:
    comparable_string_view_factory() = default;
    comparable_string_view_factory(string const & s_)
            : s(s_) {
        suffix_array(s, sa, rank);
        vector<int> lcp_ = longest_common_prefix_array(s, sa, rank);
        lcp = sparse_table<min_semilattice>(lcp_);
    }
    comparable_string_view make_view(int l, int r) const {
        assert (0 <= l and l <= r and r <= s.length());
        return comparable_string_view(this, l, r);
    }
private:
    int strcmp(int l1, int r1, int l2, int r2) const {
        int rank_l, rank_r; tie(rank_l, rank_r) = minmax({ rank[l1], rank[l2] });
        int k = lcp.range_concat(rank_l, rank_r);
        if (min(r1 - l1, r2 - l2) <= k) {
            return (r1 - l1) - (r2 - l2);
        } else {
            return rank[l1] - rank[l2];
        }
    }
};
typedef comparable_string_view_factory::comparable_string_view comparable_string_view;

unittest {
    default_random_engine gen;
    REP (iteration, 100) {
        int length = uniform_int_distribution<int>(10, 100)(gen);
        string s;
        REP (i, length) {
            s += uniform_int_distribution<char>('A', 'Z')(gen);
        }
        comparable_string_view_factory factory(s);
        REP (iteration, 100) {
            int l1 = uniform_int_distribution<int>(0, length / 2)(gen);
            int r1 = uniform_int_distribution<int>(l1, length)(gen);
            int l2 = uniform_int_distribution<int>(0, length / 2)(gen);
            int r2 = uniform_int_distribution<int>(l2, length)(gen);
            auto view1 = factory.make_view(l1, r1);
            auto view2 = factory.make_view(l2, r2);
            auto sub1 = s.substr(l1, r1 - l1);
            auto sub2 = s.substr(l2, r2 - l2);
            assert ((view1 < view2) == (sub1 < sub2));
        }
    }
}
