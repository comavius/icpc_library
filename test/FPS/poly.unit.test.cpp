#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"
#include <source_location>
ll normalize_coeff(ll x) {
   x %= mod;
   return x < 0 ? x + mod : x;
}
ll power(ll a, ll n) {
   ll r = 1;
   while(n) {
      if(n & 1) r = r * a % mod;
      a = a * a % mod;
      n >>= 1;
   }
   return r;
}
vl product(const vl& a, const vl& b) {
   vl r(a.empty() || b.empty() ? 0 : si(a) + si(b) - 1);
   rep(i, si(a)) rep(j, si(b)) r[i + j] = (r[i + j] + a[i] * b[j]) % mod;
   return r;
}
vl inverse(const vl& a, int n) {
   vl r(n);
   if(!n) return r;
   r[0] = power(a[0], mod - 2);
   rep(k, 1, n) {
      ll sum = 0;
      rep(i, 1, min<ll>(k + 1, si(a))) sum = (sum + a[i] * r[k - i]) % mod;
      r[k] = normalize_coeff(-sum) * r[0] % mod;
   }
   return r;
}
void trim(vl& a) {
   while(!a.empty() && !a.back()) a.pop_back();
}
pair<vl, vl> divide(vl a, vl b) {
   trim(a);
   trim(b);
   vl q(max(0, si(a) - si(b) + 1));
   while(a.size() >= b.size()) {
      int k = si(a) - si(b);
      ll c = a.back() * power(b.back(), mod - 2) % mod;
      q[k] = c;
      rep(i, si(b)) a[k + i] = normalize_coeff(a[k + i] - c * b[i] % mod);
      trim(a);
   }
   trim(q);
   return {q, a};
}
fps make(const vl& a) { return fps(vm(all(a))); }
vl coeff(const fps& a) {
   vl r;
   for(auto x : a.v) r.eb(x.x);
   return r;
}
void same(const fps& a, vl expected, bool canonical = false, source_location where = source_location::current()) {
   auto actual = coeff(a);
   if(canonical) {
      trim(actual);
      trim(expected);
   }
   if(actual != expected) {
      cerr << "line=" << where.line() << " actual:";
      for(auto x : actual) cerr << ' ' << x;
      cerr << " expected:";
      for(auto x : expected) cerr << ' ' << x;
      cerr << endl;
   }
   assert(actual == expected);
}
int main() {
   mt19937 rng(20261103);
   rep(step, 160) {
      int n = step % 65;
      vl a(1 + rng() % 40), b(1 + rng() % 20);
      for(auto& x : a) x = rng() % mod;
      for(auto& x : b) x = rng() % mod;
      a[0] = 1;
      b.back() = 1;
      auto f = make(a), g = make(b);
      vl sum(max(si(a), si(b))), difference = sum, negative = a;
      rep(i, si(sum)) {
         sum[i] = normalize_coeff(f.freq(i).x + g.freq(i).x);
         difference[i] = normalize_coeff(f.freq(i).x - g.freq(i).x);
      }
      for(auto& x : negative) x = normalize_coeff(-x);
      same(-f, negative);
      same(f + g, sum);
      same(f - g, difference);
      same(f * g, product(a, b));
      auto h = f;
      h += g;
      same(h, sum);
      h = f;
      h -= g;
      same(h, difference);
      h = f;
      h *= g;
      same(h, product(a, b));
      auto [q, r] = divide(a, b);
      same(f / g, q, true);
      same(f % g, r, true);
      h = f;
      h /= g;
      same(h, q, true);
      h = f;
      h %= g;
      same(h, r, true);
      same(f.inv(n), inverse(a, n));
      vl logarithm(n), exponential(n), root(n);
      if(n) exponential[0] = root[0] = 1;
      auto ai = inverse(a, n);
      rep(k, 1, n) {
         ll value = 0;
         rep(i, 1, min<ll>(k + 1, si(a))) value = (value + i * a[i] % mod * ai[k - i]) % mod;
         logarithm[k] = value * power(k, mod - 2) % mod;
         value = 0;
         rep(i, 1, k) value = (value + root[i] * root[k - i]) % mod;
         root[k] = normalize_coeff((k < si(a) ? a[k] : 0) - value) * power(2, mod - 2) % mod;
      }
      same(f.log(n), logarithm);
      same(f.sqrt(n), root);
      vl e = a;
      e[0] = 0;
      rep(k, 1, n) {
         ll value = 0;
         rep(i, 1, min<ll>(k + 1, si(e))) value = (value + i * e[i] % mod * exponential[k - i]) % mod;
         exponential[k] = value * power(k, mod - 2) % mod;
      }
      same(make(e).exp(n), exponential);
      int exponent = step % 5;
      vl expected{1};
      rep(i, exponent) {
         expected = product(expected, a);
         if(si(expected) > n) expected.resize(n);
      }
      expected.resize(n);
      same(f.pow(exponent, n), expected);
      auto modular = vl{1};
      rep(i, exponent) modular = divide(product(modular, a), b).second;
      same(f.pow_mod(exponent, g), modular, true);
      vl prefix(a.begin(), a.begin() + min(n, si(a)));
      same(f.pre(n), prefix);
      auto reversed = a;
      reverse(all(reversed));
      same(f.rev(), reversed);
      auto shifted = a;
      shifted.insert(shifted.begin(), 3, 0);
      same(f << 3, shifted);
      h = f;
      h <<= 3;
      same(h, shifted);
      shifted = si(a) <= 3 ? vl{} : vl(a.begin() + 3, a.end());
      same(f >> 3, shifted);
      h = f;
      h >>= 3;
      same(h, shifted);
      vl derivative(max(0, si(a) - 1));
      rep(i, 1, si(a)) derivative[i - 1] = a[i] * i % mod;
      same(f.diff(), derivative);
      auto integral = a;
      integral.insert(integral.begin(), 0);
      rep(i, 1, si(integral)) integral[i] = integral[i] * power(i, mod - 2) % mod;
      same(f.integ(), integral);
      same((f * mint(7)) / mint(7), a);
      h = f;
      h *= mint(7);
      h /= mint(7);
      same(h, a);
   }
   auto zero = make({0, 0});
   zero.shrink();
   assert(zero.size() == 0);
   zero.emplace_back(7);
   zero.resize(4);
   same(zero, {7, 0, 0, 0});
   auto leading = make({0, 0, 3, 1});
   same(leading.pow(3, 9), {0, 0, 0, 0, 0, 0, 27, 27, 9});
   auto empty = fps();
   same(empty.pow(0, 0), {});
   same(empty.exp(8), {1, 0, 0, 0, 0, 0, 0, 0});
   puts("Hello World");
}
