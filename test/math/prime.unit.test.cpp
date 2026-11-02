#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
mt19937_64 engine;
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r - 1)(engine); }
#include "src/math/prime.hpp"
#include "src/math/primitive-root.hpp"
int main() {
   // Official primality/factorize inputs are positive and at most 10^18.
   assert(!is_prime(0) && !is_prime(-1) && !is_prime(LLONG_MIN));
   assert(is_prime((1LL << 61) - 1));
   assert(!is_prime(LLONG_MAX));
   for(unsigned seed : {0U, 1U, 20261103U}) {
      engine.seed(seed);
      auto factors = factor(LLONG_MAX);
      sort(all(factors));
      if(factors != vl{7, 7, 73, 127, 337, 92737, 649657}) cerr << "seed=" << seed << endl;
      assert((factors == vl{7, 7, 73, 127, 337, 92737, 649657}));
   }
   // pow_mod itself has no matching official task; exercise its integer type contract.
   rep(md, 1, 40) rep(a, 40) rep(e, 12) {
      ll expected = 1 % md;
      rep(i, e) expected = expected * a % md;
      assert(pow_mod<ll>(a, e, md) == expected);
   }
   puts("Hello World");
}
