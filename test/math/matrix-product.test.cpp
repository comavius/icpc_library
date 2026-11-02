#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/matrix.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m, k;
   cin >> n >> m >> k;
   M<mint> a(n, m), b(m, k);
   for(auto& row : a.a)
      for(auto& x : row) cin >> x.x;
   for(auto& row : b.a)
      for(auto& x : row) cin >> x.x;
   auto result = a * b;
   for(auto& row : result.a) {
      for(auto x : row) cout << x.x << ' ';
      cout << '\n';
   }
}
