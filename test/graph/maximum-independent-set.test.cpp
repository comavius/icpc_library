#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "test/template.hpp"
#include "src/graph/maximum-independent-set.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   vector<vi> g(n);
   rep(i, m) {
      int u, v; cin >> u >> v;
      g[u].eb(v); g[v].eb(u);
   }
   auto chosen = maximum_independent_set(g);
   cout << popcount(chosen) << '\n';
   rep(i, n) if(chosen >> i & 1) cout << i << ' ';
   cout << '\n';
}
