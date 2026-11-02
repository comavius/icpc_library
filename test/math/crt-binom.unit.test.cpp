#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/ExtGCD.hpp"
#include "src/math/crt.hpp"
#include "src/math/binom.hpp"
#include "src/math/lagrange-hokan.hpp"
ll residue(ll a, ll m) {
   a %= m;
   return a < 0 ? a + m : a;
}
int main() {
   for(ll a : {0LL, 1LL, 2LL, 7LL, LLONG_MAX - 2, LLONG_MAX})
      for(ll b : {0LL, 1LL, 2LL, 11LL, LLONG_MAX - 2, LLONG_MAX}) {
         ll x, y;
         ll g = extgcd(a, b, x, y);
         assert(g == gcd(a, b) && i128(a) * x + i128(b) * y == g);
      }
   rep(m, 2, 101) rep(a, 1, m) if(gcd(a, m) == 1) assert(i128(a) * inv_mod(a, m) % m == 1);
   assert(inv_mod(LLONG_MAX - 2, LLONG_MAX) == (LLONG_MAX - 1) / 2);
   assert((crt({1}, {LLONG_MAX}) == pll{1, LLONG_MAX}));
   assert((crt({LLONG_MIN}, {LLONG_MAX}) == pll{LLONG_MAX - 1, LLONG_MAX}));
   assert((crt({}, {}) == pll{0, 1}));
   mt19937 rng(20261103);
   rep(step, 2000) {
      int k = rng() % 4;
      vl b(k), m(k);
      ll md = 1;
      rep(i, k) {
         b[i] = int(rng() % 201) - 100;
         m[i] = 1 + rng() % 12;
         md = lcm(md, m[i]);
      }
      ll expected = -1;
      rep(r, md) {
         bool valid = true;
         rep(i, k) if(residue(b[i], m[i]) != r % m[i]) valid = false;
         if(valid) {
            expected = r;
            break;
         }
      }
      auto actual = crt(b, m);
      assert(actual == (expected < 0 ? pll{0, -1} : pll{expected, md}));
   }
   pre();
   vector<vl> pascal(101, vl(101));
   pascal[0][0] = 1;
   rep(n, 101) {
      if(n) {
         pascal[n][0] = 1;
         rep(k, 1, n + 1) pascal[n][k] = (pascal[n - 1][k - 1] + pascal[n - 1][k]) % mod;
      }
      rep(k, -1, n + 2) assert(C(n, k).x == (k < 0 || k > n ? 0 : pascal[n][k]));
   }
   assert(C(N - 1, 0).x == 1 && C(N - 1, 1).x == N - 1 && C(N - 1, N - 1).x == 1);
   rep(step, 100) {
      vl coefficients(1 + rng() % 8);
      for(auto& x : coefficients) x = rng() % mod;
      auto evaluate = [&](ll t) {
         ll value = 0;
         for(auto it = coefficients.rbegin(); it != coefficients.rend(); ++it)
            value = (i128(value) * (t % mod) + *it) % mod;
         return value;
      };
      vm y(si(coefficients));
      rep(i, si(y)) y[i] = evaluate(i);
      for(ll t : {0LL, 1LL, 7LL, 20LL, 1LL * mod + 3, LLONG_MAX}) assert(lagrange_polynomial(y, t).x == evaluate(t));
   }
   puts("Hello World");
}
