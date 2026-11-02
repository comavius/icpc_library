#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "test/template.hpp"
#include "src/flow/bipartite-matching.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m, e;
   cin >> n >> m >> e;
   Bimatch graph(n, m);
   rep(i, e) {
      int u, v;
      cin >> u >> v;
      graph.add(u, v);
   }
   cout << graph.match() << '\n';
   rep(v, m) if(graph.mc[v] >= 0) cout << graph.mc[v] << ' ' << v << '\n';
}
