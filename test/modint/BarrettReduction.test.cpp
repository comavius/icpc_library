#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/BarrettReduction.hpp"
#include "test/modint/mint_checks.hpp"
int main() {
   check_mint();
   auto check = [](U md, U a, U b) {
      assert(md && __uint128_t(a) * b <= ULLONG_MAX);
      U actual = Barret(md).mul(a, b), expected = __uint128_t(a) * b % md;
      if(actual != expected) cerr << "seed=20261103 mod=" << md << " a=" << a << " b=" << b << endl;
      assert(actual == expected);
   };
   for(U md : {1ULL, 2ULL, 3ULL, 65536ULL, (1ULL << 31) - 1, 1ULL << 31, (1ULL << 32) - 1}) {
      for(U a : {0ULL, 1ULL, 2ULL, 3ULL, 0xffffffffULL, ULLONG_MAX}) {
         check(md, a, 0);
         check(md, a, 1);
         if(a <= 0xffffffffULL) check(md, a, 0xffffffffULL);
      }
   }
   rep(md, 1, 65) rep(a, 65) rep(b, 65) check(md, a, b);
   mt19937 rng(20261103);
   rep(i, 1000) {
      U md = rng(), a = rng(), b = rng();
      if(md) check(md, a, b);
   }
   puts("Hello World");
}
