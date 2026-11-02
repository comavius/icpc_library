#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   fps a(n), b(m);
   for(auto& x : a.v) cin >> x.x;
   for(auto& x : b.v) cin >> x.x;
   auto q = a / b, r = a % b;
   q.shrink();
   r.shrink();
   cout << q.size() << ' ' << r.size() << '\n';
   for(auto x : q.v) cout << x.x << ' ';
   cout << '\n';
   for(auto x : r.v) cout << x.x << ' ';
   cout << '\n';
}
