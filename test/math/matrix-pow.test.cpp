#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/matrix.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n;
   ll k;
   cin >> n >> k;
   M<mint> a(n);
   for(auto& row : a.a)
      for(auto& x : row) cin >> x.x;
   auto result = a ^ k;
   for(auto& row : result.a) {
      for(auto x : row) cout << x.x << ' ';
      cout << '\n';
   }
}
