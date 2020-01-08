struct pma_t { // Aho-Corasick
    pma_t* next[26];
    pma_t* fail;
    int accept;
};
pma_t *ac_new() {
    pma_t *pma = new pma_t;
    *pma = {};
    return pma;
}
void ac_add_pattern(pma_t *pma, string const & pattern) { // O(m)
    for (char c : pattern) { // make trie
        if (pma->next[c-'a'] == nullptr) {
            pma->next[c-'a'] = ac_new();
        }
        pma = pma->next[c-'a'];
    }
    pma->accept += 1;
}
void ac_construct_links(pma_t *pma) { // O(m)
    queue<pma_t *> que; // make failure link using bfs
    repeat (c,26) {
        if (pma->next[c]) {
            pma->next[c]->fail = pma;
            que.push(pma->next[c]);
        } else {
            pma->next[c] = pma;
        }
    }
    while (not que.empty()) {
        pma_t *now = que.front(); que.pop();
        repeat (c,26) {
            if (now->next[c]){
                pma_t *nxt = now->fail;
                while (not nxt->next[c]) nxt = nxt->fail;
                now->next[c]->fail = nxt->next[c];
                now->next[c]->accept += nxt->next[c]->accept;
                que.push(now->next[c]);
            }
        }
    }
}
int ac_match(pma_t *pma, string const & target) { // O(n)
    int result = 0;
    for (char c : target) {
        while (not pma->next[c-'a']) pma = pma->fail;
        pma = pma->next[c-'a'];
        result += pma->accept;
    }
    return result;
}
void ac_delete(pma_t *pma, unordered_set<pma_t *> & deleted) {
    deleted.insert(pma);
    repeat (c,26) if (pma->next[c] and not deleted.count(pma)) {
        ac_delete(pma->next[c], deleted);
    }
    delete pma;
}
void ac_delete(pma_t *pma) {
    unordered_set<pma_t *> deleted;
    ac_delete(pma, deleted);
}
