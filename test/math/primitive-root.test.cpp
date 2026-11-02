#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"
#include "test/template.hpp"
#include "src/template/rnd.hpp"
#include "src/math/prime.hpp"
#include "src/math/primitive-root.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int q;
   cin >> q;
   while(q--) {
      ll p;
      cin >> p;
      cout << primitive_root(p) << '\n';
   }
}
