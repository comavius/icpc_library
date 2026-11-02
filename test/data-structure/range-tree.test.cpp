#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "src/template/1template.hpp"
#include "src/data-structure/segtree.hpp"
#include "src/data-structure/segtree-2d.hpp"
ll add_value(ll a, ll b) { return a + b; }
ll zero_value() { return 0; }
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, q;
   cin >> n >> q;
   map<pll, ll> values;
   rep(i, n) {
      ll x, y, w;
      cin >> x >> y >> w;
      values[{x, y}] += w;
   }
   vector<array<ll, 5>> operations;
   rep(i, q) {
      int type;
      cin >> type;
      if(!type) {
         ll x, y, w;
         cin >> x >> y >> w;
         values.try_emplace({x, y}, 0);
         operations.push_back({0, x, y, w, 0});
      } else {
         ll l, d, r, u;
         cin >> l >> d >> r >> u;
         operations.push_back({1, l, d, r, u});
      }
   }
   vector<pll> coordinates;
   vl weights;
   for(auto [p, w] : values) {
      coordinates.eb(p);
      weights.eb(w);
   }
   RangeTree<ll, add_value, zero_value> tree(coordinates, weights);
   for(auto [type, a, b, c, d] : operations) {
      if(type == 0) tree.update(a, b, values[{a, b}] += c);
      else cout << tree.query(a, b, c, d) << '\n';
   }
}
