#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "test/template.hpp"
#include "src/data-structure/line_container.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, q; cin >> n >> q;
   LineContainer<true> lines;
   rep(i, n) { ll a, b; cin >> a >> b; lines.add(a, b); }
   rep(i, q) {
      int type; cin >> type;
      if(type == 0) { ll a, b; cin >> a >> b; lines.add(a, b); }
      else { ll x; cin >> x; cout << lines.query(x) << '\n'; }
   }
}
