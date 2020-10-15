---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree_beats.hpp
    title: "Segment Tree Beats (range {chmin, chmax, add, update} + range {min, max,\
      \ sum}, \u5B8C\u5168\u4E8C\u5206\u6728)"
  - icon: ':heavy_check_mark:'
    path: hack/fastio.hpp
    title: hack/fastio.hpp
  - icon: ':heavy_check_mark:'
    path: utils/macros.hpp
    title: utils/macros.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"data_structure/segment_tree_beats.yosupo.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\n\
    #line 2 \"data_structure/segment_tree_beats.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <climits>\n#include <cstdint>\n#include <vector>\n#line\
    \ 2 \"utils/macros.hpp\"\n#define REP(i, n) for (int i = 0; (i) < (int)(n); ++\
    \ (i))\n#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))\n#define\
    \ REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))\n#define REP3R(i, m,\
    \ n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))\n#define ALL(x) std::begin(x),\
    \ std::end(x)\n#line 8 \"data_structure/segment_tree_beats.hpp\"\n\n/**\n * @brief\
    \ Segment Tree Beats (range {chmin, chmax, add, update} + range {min, max, sum},\
    \ \u5B8C\u5168\u4E8C\u5206\u6728)\n * @docs data_structure/segment_tree_beats.md\n\
    \ * @see https://codeforces.com/blog/entry/57319\n */\nclass segment_tree_beats\
    \ {\n    // MEMO: values for queries (max, min, lazy_add, and lazy_update) already\
    \ apply to the current node; but not for children\n    typedef struct {\n    \
    \    int64_t max;\n        int64_t max_second;\n        int max_count;\n     \
    \   int64_t min;\n        int64_t min_second;\n        int min_count;\n      \
    \  int64_t lazy_add;\n        int64_t lazy_update;\n        int64_t sum;\n   \
    \ } value_type;\n\n    int n;\n    std::vector<value_type> a;\n\npublic:\n   \
    \ segment_tree_beats() = default;\n    segment_tree_beats(int n_) {\n        n\
    \ = 1; while (n < n_) n *= 2;\n        a.resize(2 * n - 1);\n        tag<UPDATE>(0,\
    \ 0);\n    }\n    template <class InputIterator>\n    segment_tree_beats(InputIterator\
    \ first, InputIterator last) {\n        int n_ = std::distance(first, last);\n\
    \        n = 1; while (n < n_) n *= 2;\n        a.resize(2 * n - 1);\n       \
    \ REP (i, n_) {\n            tag<UPDATE>(n - 1 + i, *(first + i));\n        }\n\
    \        REP3 (i, n_, n) {\n            tag<UPDATE>(n - 1 + i, 0);\n        }\n\
    \        REP_R (i, n - 1) {\n            update(i);\n        }\n    }\n\n    void\
    \ range_chmin(int l, int r, int64_t value) {  // 0-based, [l, r)\n        assert\
    \ (0 <= l and l <= r and r <= n);\n        range_apply<CHMIN>(0, 0, n, l, r, value);\n\
    \    }\n    void range_chmax(int l, int r, int64_t value) {  // 0-based, [l, r)\n\
    \        assert (0 <= l and l <= r and r <= n);\n        range_apply<CHMAX>(0,\
    \ 0, n, l, r, value);\n    }\n    void range_add(int l, int r, int64_t value)\
    \ {  // 0-based, [l, r)\n        assert (0 <= l and l <= r and r <= n);\n    \
    \    range_apply<ADD>(0, 0, n, l, r, value);\n    }\n    void range_update(int\
    \ l, int r, int64_t value) {  // 0-based, [l, r)\n        assert (0 <= l and l\
    \ <= r and r <= n);\n        range_apply<UPDATE>(0, 0, n, l, r, value);\n    }\n\
    \n    int64_t range_min(int l, int r) {  // 0-based, [l, r)\n        assert (0\
    \ <= l and l <= r and r <= n);\n        return range_get<MIN>(0, 0, n, l, r);\n\
    \    }\n    int64_t range_max(int l, int r) {  // 0-based, [l, r)\n        assert\
    \ (0 <= l and l <= r and r <= n);\n        return range_get<MAX>(0, 0, n, l, r);\n\
    \    }\n    int64_t range_sum(int l, int r) {  // 0-based, [l, r)\n        assert\
    \ (0 <= l and l <= r and r <= n);\n        return range_get<SUM>(0, 0, n, l, r);\n\
    \    }\n\nprivate:\n    static constexpr char CHMIN = 0;\n    static constexpr\
    \ char CHMAX = 1;\n    static constexpr char ADD = 2;\n    static constexpr char\
    \ UPDATE = 3;\n    static constexpr char MIN = 10;\n    static constexpr char\
    \ MAX = 11;\n    static constexpr char SUM = 12;\n\n    template <char TYPE>\n\
    \    void range_apply(int i, int il, int ir, int l, int r, int64_t g) {\n    \
    \    if (ir <= l or r <= il or break_condition<TYPE>(i, g)) {\n            //\
    \ break\n        } else if (l <= il and ir <= r and tag_condition<TYPE>(i, g))\
    \ {\n            tag<TYPE>(i, g);\n        } else {\n            pushdown(i);\n\
    \            range_apply<TYPE>(2 * i + 1, il, (il + ir) / 2, l, r, g);\n     \
    \       range_apply<TYPE>(2 * i + 2, (il + ir) / 2, ir, l, r, g);\n          \
    \  update(i);\n        }\n    }\n    template <char TYPE>\n    inline bool break_condition(int\
    \ i, int64_t g) {\n        switch (TYPE) {\n            case CHMIN: return a[i].max\
    \ <= g;\n            case CHMAX: return g <= a[i].min;\n            case ADD:\
    \ return false;\n            case UPDATE: return false;\n            default:\
    \ assert (false);\n        }\n    }\n    template <char TYPE>\n    inline bool\
    \ tag_condition(int i, int64_t g) {\n        switch (TYPE) {\n            case\
    \ CHMIN: return a[i].max_second < g and g < a[i].max;\n            case CHMAX:\
    \ return a[i].min < g and g < a[i].min_second;\n            case ADD: return true;\n\
    \            case UPDATE: return true;\n            default: assert (false);\n\
    \        }\n    }\n    template <char TYPE>\n    inline void tag(int i, int64_t\
    \ g) {\n        int length = n >> (32 - __builtin_clz(i + 1) - 1);\n        if\
    \ (TYPE == CHMIN) {\n            if (a[i].max == a[i].min or g <= a[i].min) {\n\
    \                tag<UPDATE>(i, g);\n                return;\n            }\n\
    \            if (a[i].max != INT64_MIN) {\n                a[i].sum -= a[i].max\
    \ * a[i].max_count;\n            }\n            a[i].max = g;\n            a[i].min_second\
    \ = std::min(a[i].min_second, g);\n            if (a[i].lazy_update != INT64_MAX)\
    \ {\n                a[i].lazy_update = std::min(a[i].lazy_update, g);\n     \
    \       }\n            a[i].sum += g * a[i].max_count;\n        } else if (TYPE\
    \ == CHMAX) {\n            if (a[i].max == a[i].min or a[i].max <= g) {\n    \
    \            tag<UPDATE>(i, g);\n                return;\n            }\n    \
    \        if (a[i].min != INT64_MAX) {\n                a[i].sum -= a[i].min *\
    \ a[i].min_count;\n            }\n            a[i].min = g;\n            a[i].max_second\
    \ = std::max(a[i].max_second, g);\n            if (a[i].lazy_update != INT64_MAX)\
    \ {\n                a[i].lazy_update = std::max(a[i].lazy_update, g);\n     \
    \       }\n            a[i].sum += g * a[i].min_count;\n        } else if (TYPE\
    \ == ADD) {\n            if (a[i].max != INT64_MAX) {\n                a[i].max\
    \ += g;\n            }\n            if (a[i].max_second != INT64_MIN) {\n    \
    \            a[i].max_second += g;\n            }\n            if (a[i].min !=\
    \ INT64_MIN) {\n                a[i].min += g;\n            }\n            if\
    \ (a[i].min_second != INT64_MAX) {\n                a[i].min_second += g;\n  \
    \          }\n            a[i].lazy_add += g;\n            if (a[i].lazy_update\
    \ != INT64_MAX) {\n                a[i].lazy_update += g;\n            }\n   \
    \         a[i].sum += g * length;\n        } else if (TYPE == UPDATE) {\n    \
    \        a[i].max = g;\n            a[i].max_second = INT64_MIN;\n           \
    \ a[i].max_count = length;\n            a[i].min = g;\n            a[i].min_second\
    \ = INT64_MAX;\n            a[i].min_count = length;\n            a[i].lazy_add\
    \ = 0;\n            a[i].lazy_update = INT64_MAX;\n            a[i].sum = g *\
    \ length;\n        } else {\n            assert (false);\n        }\n    }\n \
    \   void pushdown(int i) {\n        int l = 2 * i + 1;\n        int r = 2 * i\
    \ + 2;\n        // update\n        if (a[i].lazy_update != INT64_MAX) {\n    \
    \        tag<UPDATE>(l, a[i].lazy_update);\n            tag<UPDATE>(r, a[i].lazy_update);\n\
    \            a[i].lazy_update = INT64_MAX;\n            return;\n        }\n \
    \       // add\n        if (a[i].lazy_add != 0) {\n            tag<ADD>(l, a[i].lazy_add);\n\
    \            tag<ADD>(r, a[i].lazy_add);\n            a[i].lazy_add = 0;\n   \
    \     }\n        // chmin\n        if (a[i].max < a[l].max) {\n            tag<CHMIN>(l,\
    \ a[i].max);\n        }\n        if (a[i].max < a[r].max) {\n            tag<CHMIN>(r,\
    \ a[i].max);\n        }\n        // chmax\n        if (a[l].min < a[i].min) {\n\
    \            tag<CHMAX>(l, a[i].min);\n        }\n        if (a[r].min < a[i].min)\
    \ {\n            tag<CHMAX>(r, a[i].min);\n        }\n    }\n    void update(int\
    \ i) {\n        int l = 2 * i + 1;\n        int r = 2 * i + 2;\n        // chmin\n\
    \        std::vector<int64_t> b { a[l].max, a[l].max_second, a[r].max, a[r].max_second\
    \ };\n        std::sort(b.rbegin(), b.rend());\n        b.erase(std::unique(ALL(b)),\
    \ b.end());\n        a[i].max = b[0];\n        a[i].max_second = b[1];\n     \
    \   a[i].max_count = (b[0] == a[l].max ? a[l].max_count : 0) + (b[0] == a[r].max\
    \ ? a[r].max_count : 0);\n        // chmax\n        std::vector<int64_t> c { a[l].min,\
    \ a[l].min_second, a[r].min, a[r].min_second };\n        std::sort(ALL(c));\n\
    \        c.erase(std::unique(ALL(c)), c.end());\n        a[i].min = c[0];\n  \
    \      a[i].min_second = c[1];\n        a[i].min_count = (c[0] == a[l].min ? a[l].min_count\
    \ : 0) + (c[0] == a[r].min ? a[r].min_count : 0);\n        // add\n        a[i].lazy_add\
    \ = 0;\n        // update\n        a[i].lazy_update = INT64_MAX;\n        // sum\n\
    \        a[i].sum = a[l].sum + a[r].sum;\n    }\n\n    template <char TYPE>\n\
    \    int64_t range_get(int i, int il, int ir, int l, int r) {\n        if (ir\
    \ <= l or r <= il) {\n            switch (TYPE) {\n                case MIN: return\
    \ INT64_MAX;\n                case MAX: return INT64_MIN;\n                case\
    \ SUM: return 0;\n                default: assert (false);\n            }\n  \
    \      } else if (l <= il and ir <= r) {\n            // base\n            switch\
    \ (TYPE) {\n                case MIN: return a[i].min;\n                case MAX:\
    \ return a[i].max;\n                case SUM: return a[i].sum;\n             \
    \   default: assert (false);\n            }\n        } else {\n            pushdown(i);\n\
    \            int64_t value_l = range_get<TYPE>(2 * i + 1, il, (il + ir) / 2, l,\
    \ r);\n            int64_t value_r = range_get<TYPE>(2 * i + 2, (il + ir) / 2,\
    \ ir, l, r);\n            // mult\n            switch (TYPE) {\n             \
    \   case MIN: return std::min(value_l, value_r);\n                case MAX: return\
    \ std::max(value_l, value_r);\n                case SUM: return value_l + value_r;\n\
    \                default: assert (false);\n            }\n        }\n    }\n};\n\
    #line 3 \"data_structure/segment_tree_beats.yosupo.test.cpp\"\n\n#line 3 \"hack/fastio.hpp\"\
    \n#include <cstdio>\n#include <string>\n#include <type_traits>\n\ntemplate <class\
    \ Char, std::enable_if_t<std::is_same_v<Char, char>, int> = 0>\ninline Char in()\
    \ { return getchar_unlocked(); }\ntemplate <class String, std::enable_if_t<std::is_same_v<String,\
    \ std::string>, int> = 0>\ninline std::string in() {\n    char c; do { c = getchar_unlocked();\
    \ } while (isspace(c));\n    std::string s;\n    do { s.push_back(c); } while\
    \ (not isspace(c = getchar_unlocked()));\n    return s;\n}\ntemplate <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer> and not std::is_same_v<Integer,\
    \ char>, int> = 0>\ninline Integer in() {\n    char c; do { c = getchar_unlocked();\
    \ } while (isspace(c));\n    if (std::is_signed<Integer>::value and c == '-')\
    \ return -in<Integer>();\n    Integer n = 0;\n    do { n = n * 10 + c - '0'; }\
    \ while (not isspace(c = getchar_unlocked()));\n    return n;\n}\n\ntemplate <class\
    \ Char, std::enable_if_t<std::is_same_v<Char, char>, int> = 0>\ninline void out(char\
    \ c) { putchar_unlocked(c); }\ntemplate <class String, std::enable_if_t<std::is_same_v<String,\
    \ std::string>, int> = 0>\ninline void out(const std::string & s) { for (char\
    \ c : s) putchar_unlocked(c); }\ntemplate <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\ninline void out(Integer n) {\n    char s[20];\n    int i = 0;\n \
    \   if (std::is_signed<Integer>::value and n < 0) { putchar_unlocked('-'); n *=\
    \ -1; }\n    do { s[i ++] = n % 10; n /= 10; } while (n);\n    while (i) putchar_unlocked(s[--\
    \ i] + '0');\n}\n#line 8 \"data_structure/segment_tree_beats.yosupo.test.cpp\"\
    \n\nint main() {\n    int n = in<int>();\n    int q = in<int>();\n\n    std::vector<int64_t>\
    \ a(n);\n    REP (i, n) {\n        a[i] = in<int64_t>();\n    }\n    segment_tree_beats\
    \ beats(ALL(a));\n\n    while (q --) {\n        int ty = in<int>();\n        int\
    \ l = in<int>();\n        int r = in<int>();\n        if (ty == 0) {\n       \
    \     int64_t b = in<int64_t>();\n            beats.range_chmin(l, r, b);\n  \
    \      } else if (ty == 1) {\n            int64_t b = in<int64_t>();\n       \
    \     beats.range_chmax(l, r, b);\n        } else if (ty == 2) {\n           \
    \ int64_t b = in<int64_t>();\n            beats.range_add(l, r, b);\n        }\
    \ else {\n            int64_t sum = beats.range_sum(l, r);\n            out<int64_t>(sum);\n\
    \            out<char>('\\n');\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n#include \"data_structure/segment_tree_beats.hpp\"\n\n#include <cstdint>\n#include\
    \ <vector>\n#include \"utils/macros.hpp\"\n#include \"hack/fastio.hpp\"\n\nint\
    \ main() {\n    int n = in<int>();\n    int q = in<int>();\n\n    std::vector<int64_t>\
    \ a(n);\n    REP (i, n) {\n        a[i] = in<int64_t>();\n    }\n    segment_tree_beats\
    \ beats(ALL(a));\n\n    while (q --) {\n        int ty = in<int>();\n        int\
    \ l = in<int>();\n        int r = in<int>();\n        if (ty == 0) {\n       \
    \     int64_t b = in<int64_t>();\n            beats.range_chmin(l, r, b);\n  \
    \      } else if (ty == 1) {\n            int64_t b = in<int64_t>();\n       \
    \     beats.range_chmax(l, r, b);\n        } else if (ty == 2) {\n           \
    \ int64_t b = in<int64_t>();\n            beats.range_add(l, r, b);\n        }\
    \ else {\n            int64_t sum = beats.range_sum(l, r);\n            out<int64_t>(sum);\n\
    \            out<char>('\\n');\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - data_structure/segment_tree_beats.hpp
  - utils/macros.hpp
  - hack/fastio.hpp
  isVerificationFile: true
  path: data_structure/segment_tree_beats.yosupo.test.cpp
  requiredBy: []
  timestamp: '2020-06-13 00:00:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/segment_tree_beats.yosupo.test.cpp
layout: document
redirect_from:
- /verify/data_structure/segment_tree_beats.yosupo.test.cpp
- /verify/data_structure/segment_tree_beats.yosupo.test.cpp.html
title: data_structure/segment_tree_beats.yosupo.test.cpp
---