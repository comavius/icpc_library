#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"

// Official convolution_mod covers products. Supplement empty operands and the raw transform API only.
ll power_mod(ll a, int e) {
   ll result = 1;
   while(e) {
      if(e & 1) result = result * a % mod;
      a = a * a % mod;
      e >>= 1;
   }
   return result;
}

void check_product(const vl& a, const vl& b) {
   vl expected(a.empty() || b.empty() ? 0 : si(a) + si(b) - 1);
   rep(i, si(a)) rep(j, si(b)) expected[i + j] = (expected[i + j] + a[i] * b[j]) % mod;
   auto actual = mul(vm(all(a)), vm(all(b)));
   assert(si(actual) == si(expected));
   rep(i, si(expected)) assert(actual[i].x == expected[i]);
}

int main() {
   mt19937 rng(20261102);
   auto random_vector = [&](int n) {
      vl a(n);
      for(auto& x : a) x = rng() % mod;
      return a;
   };

   check_product({}, {});
   check_product({}, {1, 2});
   check_product({1, 2}, {});
   // Nonempty, power-of-two FFT inputs; the inverse is intentionally unnormalized.
   for(int n = 1; n <= 4096; n *= 2) {
      auto input = random_vector(n);
      vm transformed(all(input));
      fft(transformed);
      if(n <= 16) {
         ll root = power_mod(3, (mod - 1) / n);
         rep(k, n) {
            ll base = power_mod(root, k), weight = 1, expected = 0;
            rep(j, n) {
               expected = (expected + input[j] * weight) % mod;
               weight = weight * base % mod;
            }
            assert(transformed[k].x == expected);
         }
      }
      fft(transformed, true);
      rep(i, n) assert(transformed[i].x == input[i] * n % mod);
   }

   puts("Hello World");
}
