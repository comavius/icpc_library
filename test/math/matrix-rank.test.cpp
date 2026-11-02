#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/matrix.hpp"
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   M<mint> a(n, m);
   for(auto& row : a.a)
      for(auto& x : row) cin >> x.x;
   cout << GaussElimination(a).first << '\n';
}
