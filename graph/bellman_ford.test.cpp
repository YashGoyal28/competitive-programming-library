#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"
#include "graph/bellman_ford.hpp"

#include <algorithm>
#include <iostream>
#include "utils/macros.hpp"
using namespace std;

int main() {
    // input
    int v, e, root; cin >> v >> e >> root;
    vector<vector<pair<int, int64_t> > > g(v);
    REP (j, e) {
        int s, t, dist; cin >> s >> t >> dist;
        g[s].emplace_back(t, dist);
    }

    // solve
    auto dist = bellman_ford_shortest_path(root, g);

    // output
    if (count(ALL(dist), LLONG_MIN)) {
        cout << "NEGATIVE CYCLE" << endl;
    } else {
        REP (i, v) {
            if (dist[i] == LLONG_MAX) {
                cout << "INF" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
    }
    return 0;
}
