#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n;
   cin >> n;
   fps a(n);
   for(auto& x : a.v) cin >> x.x;
   auto b = a.log(n);
   rep(i, n) cout << b.freq(i).x << ' ';
   cout << '\n';
}
