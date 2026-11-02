#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/data-structure/segtree.hpp"
using A = pair<mint, mint>;
A compose(A f, A g) { return {g.first * f.first, g.first * f.second + g.second}; }
A composition_identity() { return {1, 0}; }
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, q;
   cin >> n >> q;
   vector<A> initial(n);
   for(auto& [a, b] : initial) cin >> a.x >> b.x;
   segtree<A, compose, composition_identity> tree(initial);
   rep(i, q) {
      int type;
      cin >> type;
      if(!type) {
         int p;
         A f;
         cin >> p >> f.first.x >> f.second.x;
         tree.set(p, f);
      } else {
         int l, r;
         mint x;
         cin >> l >> r >> x.x;
         auto f = tree.prod(l, r);
         cout << (f.first * x + f.second).x << '\n';
      }
   }
}
