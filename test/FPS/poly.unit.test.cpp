#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"
void same(const fps& a, vl expected) {
   vl actual;
   for(auto x : a.v) actual.eb(x.x);
   for(auto& x : expected)
      if(x < 0) x += mod;
   assert(actual == expected);
}
int main() {
   // Do not impose n=0 contracts on coefficient-count operations or exact storage lengths.
   fps empty;
   assert(empty.size() == 0 && empty.freq(0).x == 0);
   fps a(vm{1, 2, 3, 0});
   same(a.pre(10), {1, 2, 3, 0});
   same(a.pre(2), {1, 2});
   same(a.rev(), {0, 3, 2, 1});
   same(a.rev(2), {2, 1});
   same(a << 2, {0, 0, 1, 2, 3, 0});
   same(a >> 10, {});
   auto b = a;
   b <<= 2;
   b >>= 2;
   same(b, {1, 2, 3, 0});
   b.shrink();
   same(b, {1, 2, 3});
   b.resize(5);
   b.emplace_back(7);
   same(b, {1, 2, 3, 0, 0, 7});
   assert(b.freq(10).x == 0);
   same(a.diff(), {2, 6, 0});
   same(a.diff().integ(), {0, 2, 3, 0});
   b = a;
   b += a;
   same(b, {2, 4, 6, 0});
   b -= a;
   same(b, {1, 2, 3, 0});
   b *= mint(7);
   b /= mint(7);
   same(b, {1, 2, 3, 0});
   b = fps(vm{1, 1});
   b *= fps(vm{1, 1});
   same(b, {1, 2, 1});
   b /= fps(vm{1, 1});
   same(b, {1, 1});
   b %= fps(vm{1, 1});
   b.shrink();
   same(b, {});
   // No official polynomial modular-power task matches this API.
   fps f(vm{1, 1}), divisor(vm{1, 0, 1});
   vector<vl> expected{{1}, {1, 1}, {0, 2}, {-2, 2}, {-4}, {-4, -4}, {0, -8}, {8, -8}, {16}};
   rep(k, si(expected)) {
      auto r = f.pow_mod(k, divisor);
      r.shrink();
      auto e = expected[k];
      for(auto& x : e)
         if(x < 0) x += mod;
      same(r, e);
   }
   puts("Hello World");
}
