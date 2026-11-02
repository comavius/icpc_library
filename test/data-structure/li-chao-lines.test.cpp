#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "test/template.hpp"
#include "src/data-structure/li-chao.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, q;
   cin >> n >> q;
   vector<pll> initial(n);
   for(auto& [a, b] : initial) cin >> a >> b;
   vector<array<ll, 3>> operations;
   vl xs;
   rep(i, q) {
      ll t, a, b = 0;
      cin >> t >> a;
      if(!t) cin >> b;
      else xs.eb(a);
      operations.push_back({t, a, b});
   }
   if(xs.empty()) return 0;
   lctree tree(xs);
   for(auto [a, b] : initial) tree.update(a, b);
   for(auto [t, a, b] : operations) {
      if(!t) tree.update(a, b);
      else cout << tree.query(a) << '\n';
   }
}
