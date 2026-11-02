#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/matrix.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n;
   cin >> n;
   M<mint> a(n);
   for(auto& row : a.a)
      for(auto& x : row) cin >> x.x;
   cout << GaussElimination(a).second.x << '\n';
}
