#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"
#include "test/template.hpp"
#include "src/data-structure/li-chao.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, q; cin >> n >> q;
   vector<array<ll, 5>> operations;
   rep(i, n) {
      ll l, r, a, b; cin >> l >> r >> a >> b;
      operations.push_back({0,l,r,a,b});
   }
   vl coordinates;
   rep(i, q) {
      int type; cin >> type;
      if(type == 0) {
         ll l, r, a, b; cin >> l >> r >> a >> b;
         operations.push_back({0,l,r,a,b});
      } else {
         ll x; cin >> x;
         coordinates.eb(x);
         operations.push_back({1,x,0,0,0});
      }
   }
   if(coordinates.empty()) return 0;
   lctree lines(coordinates);
   for(auto [type,l,r,a,b] : operations) {
      if(type == 0) lines.update_segment(l,r,a,b);
      else {
         ll answer = lines.query(l);
         if(answer == INFL) cout << "INFINITY\n";
         else cout << answer << '\n';
      }
   }
}
