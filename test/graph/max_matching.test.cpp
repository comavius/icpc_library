#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"
#include "test/template.hpp"
#include "src/graph/max_matching.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   vector<vi> g(n);
   rep(i, m) {
      int u, v; cin >> u >> v;
      g[u].eb(v); g[v].eb(u);
   }
   auto matching = Matching(g).max_match();
   cout << matching.size() << '\n';
   for(auto [u, v] : matching) cout << u << ' ' << v << '\n';
}
