#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"
#include "src/FPS/linear-recurrence.hpp"
#include "src/FPS/relaxed-convolution.hpp"
ll normalize(ll a) {
   a %= mod;
   return a < 0 ? a + mod : a;
}
ll invert(ll a) {
   ll result = 1;
   for(int e = mod - 2; e; e >>= 1, a = a * a % mod)
      if(e & 1) result = result * a % mod;
   return result;
}
int main() {
   mt19937 rng(20261103);
   rep(step, 200) {
      int d = 1 + rng() % 12;
      vl q(d + 1), p(rng() % 20), expected(160);
      for(auto& x : q) x = rng() % mod;
      q[0] = 1 + rng() % (mod - 1);
      for(auto& x : p) x = rng() % mod;
      rep(k, si(expected)) {
         ll value = k < si(p) ? p[k] : 0;
         rep(j, 1, min<ll>(k, d) + 1) value = normalize(value - q[j] * expected[k - j] % mod);
         expected[k] = value * invert(q[0]) % mod;
      }
      for(int k : {0, 1, d - 1, d, d + 1, 79, 159})
         assert(LinearRecurrence(k, fps(vm(all(q))), fps(vm(all(p)))).x == expected[k]);
      vl initial(d);
      for(auto& x : initial) x = rng() % mod;
      expected = initial;
      expected.resize(160);
      rep(k, d, 160) {
         ll value = 0;
         rep(j, 1, d + 1) value = normalize(value - q[j] * expected[k - j] % mod);
         expected[k] = value * invert(q[0]) % mod;
      }
      for(int k : {0, d - 1, d, d + 1, 159})
         assert(kitamasa(k, fps(vm(all(q))), fps(vm(all(initial)))).x == expected[k]);
   }
   assert(LinearRecurrence(1000000000000000000LL, fps(vm{2, -2}), fps(vm{6})).x == 3);
   assert(LinearRecurrence(0, fps(vm{1}), fps()).x == 0);
   for(int n : {1, 2, 31, 32, 33, 63, 64, 65, 96, 127, 128, 129, 255, 256, 257, 1025}) {
      relaxed_multiplication stream;
      vl f(n), g(n);
      rep(k, n) {
         f[k] = rng() % mod;
         g[k] = rng() % mod;
         ll expected = 0;
         rep(i, k + 1) expected = (expected + f[i] * g[k - i]) % mod;
         assert(stream.add(f[k], g[k]).x == expected);
      }
   }
   relaxed_multiplication zero, ones;
   rep(i, 1025) {
      assert(zero.add(0, 0).x == 0);
      assert(ones.add(1, 1).x == i + 1);
   }
   puts("Hello World");
}
