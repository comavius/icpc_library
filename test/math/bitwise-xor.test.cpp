#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/xor-convolution.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int lg;
   cin >> lg;
   int n = 1 << lg;
   vm a(n), b(n);
   for(auto& x : a) cin >> x.x;
   for(auto& x : b) cin >> x.x;
   fwt(a);
   fwt(b);
   rep(i, n) a[i] *= b[i];
   fwt(a, true);
   for(auto x : a) cout << x.x << ' ';
   cout << '\n';
}
