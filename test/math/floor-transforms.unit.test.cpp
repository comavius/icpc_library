#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/floor_sum.hpp"
#include "src/math/and-or-convolution.hpp"
#include "src/math/xor-convolution.hpp"
int main() {
   rep(n, 20) rep(a, 20) rep(b, 20) rep(c, 1, 20) {
      ll expected = 0;
      rep(i, n) expected += (a * i + b) / c;
      assert(floor_sum(n, a, b, c) == expected);
   }
   assert(floor_sum(2, 1, LLONG_MAX - 1, LLONG_MAX) == 1);
   assert(floor_sum(LLONG_MAX, 1, 0, LLONG_MAX) == 0);
   assert(floor_sum(LLONG_MAX, 1, 0, (LLONG_MAX - 1) / 2) == (LLONG_MAX - 1) / 2 + 2);
   assert(floor_sum(1000000000, 1, 1000000000, 1) == 1499999999500000000LL);
   mt19937 rng(20261103);
   rep(logn, 9) rep(step, 20) {
      int n = 1 << logn;
      vl a(n), b(n);
      for(auto& x : a) x = step ? rng() % mod : 0;
      for(auto& x : b) x = step ? rng() % mod : 0;
      rep(kind, 3) {
         vl expected(n);
         rep(i, n) rep(j, n) {
            int k = kind == 0 ? (i & j) : kind == 1 ? (i | j) : (i ^ j);
            expected[k] = (expected[k] + a[i] * b[j]) % mod;
         }
         vm x(all(a)), y(all(b));
         auto transform = [&](vm& v, bool inv) {
            if(kind == 0) fzt<false>(v, inv);
            if(kind == 1) fzt<true>(v, inv);
            if(kind == 2) fwt(v, inv);
         };
         transform(x, false);
         transform(x, true);
         rep(i, n) assert(x[i].x == a[i]);
         transform(x, false);
         transform(y, false);
         rep(i, n) x[i] *= y[i];
         transform(x, true);
         rep(i, n) assert(x[i].x == expected[i]);
      }
   }
   puts("Hello World");
}
