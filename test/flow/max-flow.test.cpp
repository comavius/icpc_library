#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
#include "test/template.hpp"
#include "src/flow/flow.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   Dinic<ll> flow(n);
   rep(i, m) {
      int u, v;
      ll cap;
      cin >> u >> v >> cap;
      flow.add_edge(u, v, cap);
   }
   cout << flow.max_flow(0, n - 1) << '\n';
}
