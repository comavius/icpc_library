#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"
#include "src/FPS/relaxed-convolution.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, m;
   cin >> n >> m;
   vm a(n), b(m);
   for(auto& x : a) cin >> x.x;
   for(auto& x : b) cin >> x.x;
   relaxed_multiplication stream;
   rep(i, n + m - 1) cout << stream.add(i < n ? a[i] : mint(0), i < m ? b[i] : mint(0)).x << ' ';
   cout << '\n';
}
