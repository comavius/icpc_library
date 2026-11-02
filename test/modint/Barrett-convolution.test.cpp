#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "test/template.hpp"
#include "src/modint/BarrettReduction.hpp"
#include "src/FPS/FFT.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   vm a(n), b(m);
   for(auto& x : a) cin >> x.x;
   for(auto& x : b) cin >> x.x;
   auto c = mul(a, b);
   for(auto x : c) cout << x.x << ' ';
   cout << '\n';
}
