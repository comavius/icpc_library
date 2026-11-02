#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
mt19937_64 engine;
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r - 1)(engine); }
#include "src/math/prime.hpp"
#include "src/math/primitive-root.hpp"
vl trial(ll n) {
   vl r;
   for(ll p = 2; p * p <= n; ++p)
      while(n % p == 0) {
         r.eb(p);
         n /= p;
      }
   if(n > 1) r.eb(n);
   return r;
}
void check(ll n, vl expected) {
   auto actual = factor(n);
   sort(all(actual));
   if(actual != expected) cerr << "factor input=" << n << endl;
   assert(actual == expected);
   i128 product = 1;
   for(ll p : actual) product *= p;
   assert(product == n);
}
int main() {
   vector<bool> prime(20001, true);
   prime[0] = prime[1] = false;
   rep(p, 2, si(prime)) if(prime[p]) for(int j = p * 2; j < si(prime); j += p) prime[j] = false;
   rep(n, si(prime)) assert(is_prime(n) == prime[n]);
   for(ll n : {341LL, 561LL, 1105LL, 1729LL, 3215031751LL, 341550071728321LL, LLONG_MAX}) assert(!is_prime(n));
   assert(is_prime((1LL << 61) - 1));
   rep(md, 1, 40) rep(a, 40) rep(e, 12) {
      ll expected = 1 % md;
      rep(i, e) expected = expected * a % md;
      assert(pow_mod<ll>(a, e, md) == expected);
   }
   for(unsigned seed : {0U, 1U, 20261103U}) {
      engine.seed(seed);
      rep(n, 1, 1500) check(n, trial(n));
      check((1LL << 61) - 1, {(1LL << 61) - 1});
      check(1000000007LL * 1000000009LL, {1000000007, 1000000009});
      check(LLONG_MAX, {7, 7, 73, 127, 337, 92737, 649657});
      for(int p : {2, 3, 5, 7, 17, 97, 257, 65537, 998244353}) {
         ll g = primitive_root(p);
         assert(g >= 1 && g < p);
         for(ll d : trial(p - 1)) assert(pow_mod<i128>(g, (p - 1) / d, p) != 1);
         assert(pow_mod<i128>(g, p - 1, p) == 1);
      }
      for(ll n : {4LL, 9LL, 27LL, 49LL, 1000000007LL * 1000000009LL}) {
         ll d = pollard_single(n);
         assert(d > 1 && n % d == 0);
      }
   }
   puts("Hello World");
}
