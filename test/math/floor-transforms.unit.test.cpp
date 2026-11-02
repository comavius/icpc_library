#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/floor_sum.hpp"
#include "src/math/and-or-convolution.hpp"
#include "src/math/xor-convolution.hpp"
int main() {
   // sum_of_floor_of_linear has n>=1, a,b<c and all values <=10^9.
   rep(n, 20) rep(a, 20) rep(b, 20) rep(c, 1, 20) if(!n || a >= c || b >= c) {
      ll expected = 0;
      rep(i, n) expected += (a * i + b) / c;
      assert(floor_sum(n, a, b, c) == expected);
   }
   assert(floor_sum(2, 1, LLONG_MAX - 1, LLONG_MAX) == 1);
   assert(floor_sum(LLONG_MAX, 1, 0, LLONG_MAX) == 0);
   assert(floor_sum(LLONG_MAX, 1, 0, (LLONG_MAX - 1) / 2) == (LLONG_MAX - 1) / 2 + 2);
   // Official tasks expose convolutions, not the transform coefficients themselves.
   rep(lg, 4) {
      int n = 1 << lg;
      rep(basis, n) rep(kind, 3) {
         vm a(n);
         a[basis] = 1;
         auto transform = [&](bool inv) {
            if(kind == 0) fzt<false>(a, inv);
            if(kind == 1) fzt<true>(a, inv);
            if(kind == 2) fwt(a, inv);
         };
         transform(false);
         rep(i, n) {
            ll expected = kind == 0   ? ((basis & i) == i)
                          : kind == 1 ? ((basis & i) == basis)
                                      : ((popcount(unsigned(basis & i)) & 1) ? mod - 1 : 1);
            assert(a[i].x == expected);
         }
         transform(true);
         rep(i, n) assert(a[i].x == (i == basis));
      }
   }
   // No official bitwise-OR convolution task: check this operation separately.
   mt19937 rng(20261103);
   rep(lg, 7) {
      int n = 1 << lg;
      vl a(n), b(n), expected(n);
      for(auto& x : a) x = rng() % mod;
      for(auto& x : b) x = rng() % mod;
      rep(i, n) rep(j, n) expected[i | j] = (expected[i | j] + a[i] * b[j]) % mod;
      vm x(all(a)), y(all(b));
      fzt<true>(x);
      fzt<true>(y);
      rep(i, n) x[i] *= y[i];
      fzt<true>(x, true);
      rep(i, n) assert(x[i].x == expected[i]);
   }
   puts("Hello World");
}
