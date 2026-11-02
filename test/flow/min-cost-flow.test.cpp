#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
#include "test/template.hpp"
#include "src/flow/mcf.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   ll amount;
   cin >> n >> m >> amount;
   MCF flow(n);
   rep(i, m) {
      int u, v;
      ll cap, cost;
      cin >> u >> v >> cap >> cost;
      flow.add(u, v, cap, cost);
   }
   cout << flow.mcf(0, n - 1, amount) << '\n';
}
