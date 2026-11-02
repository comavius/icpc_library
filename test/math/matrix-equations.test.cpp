#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
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
   vector<mint> b(n);
   for(auto& x : b) cin >> x.x;
   auto solutions = LinearEquation(a, b);
   if(solutions.empty()) cout << -1 << '\n';
   else {
      cout << solutions.size() - 1 << '\n';
      for(auto& row : solutions) {
         for(auto x : row) cout << x.x << ' ';
         cout << '\n';
      }
   }
}
