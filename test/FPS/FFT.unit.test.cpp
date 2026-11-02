#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"

// Independent integer arithmetic, without mint/fft/mul in the oracle.
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
   check_product({0}, {mod - 1});
   check_product({mod - 1}, {mod - 1});
   check_product({1, 2, 3}, {4, 5});

   // Exercise both sides of min(n,m)<=30, and padding across powers of two.
   for(int n : {1, 2, 29, 30, 31, 32, 33, 63, 64, 65, 127, 128, 129}) {
      for(int m : {1, 2, 29, 30, 31, 32, 33, 63, 64, 65, 127, 128, 129}) {
         check_product(random_vector(n), random_vector(m));
      }
   }
   rep(iteration, 100) check_product(random_vector(rng() % 200), random_vector(rng() % 200));
   check_product(vl(65, 0), vl(65, mod - 1));
   check_product(vl(65, mod - 1), vl(65, mod - 1));
   vl impulse(65);
   impulse.back() = 1;
   check_product(impulse, random_vector(63));

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

   // A larger NTT case with an exact O(n+m) oracle for all-one inputs.
   const int n = 1 << 18, m = 31;
   auto large = mul(vm(n, 1), vm(m, 1));
   assert(si(large) == n + m - 1);
   rep(k, si(large)) {
      int expected = max(0, min(n - 1, int(k)) - max(0, int(k) - m + 1) + 1);
      assert(large[k].x == expected);
   }
   puts("Hello World");
}
