/**
 * @note O((E + V) log V)
 */
vector<ll> dijkstra(vector<vector<pair<int, ll> > > const & g, int root) {
    vector<ll> dist(g.size(), LLONG_MAX);
    priority_queue<pair<ll, int> > que;
    dist[root] = 0;
    que.emplace(- dist[root], root);
    while (not que.empty()) {
        ll dist_i; int i; tie(dist_i, i) = que.top(); que.pop();
        if (dist[i] < - dist_i) continue;
        for (auto it : g[i]) {
            int j; ll cost; tie(j, cost) = it;
            if (- dist_i + cost < dist[j]) {
                dist[j] = - dist_i + cost;
                que.emplace(dist_i - cost, j);
            }
        }
    }
    return dist;
}

template <typename T>
vector<T> original_dijkstra(vector<vector<pair<int, T> > > const & g, int start, T inf) { // O(V^2)
    int n = g.size();
    vector<double> dist(n, inf);
    vector<int> ixs(n); whole(iota, ixs, 0);
    dist[start] = 0;
    repeat (loop,n) {
        int i; {
            auto it = whole(min_element, ixs, [&](int i, int j) { return dist[i] < dist[j]; });
            i = *it;
            *it = ixs.back();
            ixs.pop_back();
        }
        for (auto it : g[i]) {
            int j; T cost; tie(j, cost) = it;
            setmin(dist[j], dist[i] + cost);
        }
    }
    return dist;
}

/**
 * @note generic one
 */
template <class T, class Func>
vector<T> run_dijkstra(int n, int src, Func iterate) {
    vector<T> dist(n, numeric_limits<T>::max());
    priority_queue<pair<T, int> > que;
    dist[src] = 0;
    que.emplace(- dist[src], src);
    while (not que.empty()) {
        T dist_i; int i; tie(dist_i, i) = que.top(); que.pop();
        if (dist[i] < - dist_i) continue;
        iterate(i, [&](int j, T cost) {
            if (- dist_i + cost < dist[j]) {
                dist[j] = - dist_i + cost;
                que.emplace(dist_i - cost, j);
            }
        });
    }
    return dist;
}

template <class T, class Func>
vector<int> reconstruct_dijkstra(int n, int src, int dst, vector<T> const & dist, Func iterate) {
}

template <class T, class Func>
vector<int> reconstruct_edges_dijkstra(int n, int src, int dst, vector<T> const & dist, Func iterate) {
    vector<int> edges;
    int i = dst;
    while (i != src) {
        int next = -1;
        int next_edge = -1;
        iterate(i, [&](int j, int edge, T cost) {
            if (dist[i] == dist[j] + cost) {
                next = j;
                next_edge = edge;
            }
        });
        assert (next != -1);
        i = next;
        edges.push_back(next_edge);
    }
    reverse(ALL(edges));
    return edges;
}
