#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"

// The library's sqrt is normalized to constant term 1. This test-only adapter
// supplies a modular square root and removes leading zeroes for the official task.
optional<mint> constant_root(mint a) {
   if(a.pow((mod - 1) / 2).x != 1) return nullopt;
   int m = 23;
   mint c = mint(3).pow(119), t = a.pow(119), x = a.pow(60);
   while(t.x != 1) {
      int i = 0;
      mint y = t;
      while(y.x != 1) {
         y *= y;
         ++i;
      }
      mint b = c.pow(1LL << (m - i - 1));
      x *= b;
      c = b * b;
      t *= c;
      m = i;
   }
   return x;
}
int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n;
   cin >> n;
   fps f(n);
   for(auto& x : f.v) cin >> x.x;
   int k = 0;
   while(k < n && f[k].x == 0) ++k;
   fps answer(n);
   if(k < n) {
      if(k & 1) {
         cout << -1 << '\n';
         return 0;
      }
      auto root = constant_root(f[k]);
      if(!root) {
         cout << -1 << '\n';
         return 0;
      }
      answer = (((f >> k) / f[k]).sqrt(n - k) * *root) << (k / 2);
      answer.resize(n);
   }
   for(auto x : answer.v) cout << x.x << ' ';
   cout << '\n';
}
