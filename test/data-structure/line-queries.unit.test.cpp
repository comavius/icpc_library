#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/cht.hpp"

template<bool minimum> void check_lines(vector<pll> lines) {
   CHT<minimum> cht, inc, dec;
   vector<pll> used;
   for(auto [a, b] : lines) {
      cht.add(a, b);
      inc.add(a, b);
      dec.add(a, b);
      used.eb(a, b);
      for(ll x : {-1000000000LL, -100LL, -7LL, -1LL, 0LL, 1LL, 8LL, 100LL, 1000000000LL}) {
         ll expected = minimum ? LLONG_MAX : LLONG_MIN;
         for(auto [slope, intercept] : used) {
            ll y = slope * x + intercept;
            expected = minimum ? min(expected, y) : max(expected, y);
         }
         assert(cht.query(x) == expected);
      }
   }
   for(ll x = -100; x <= 100; ++x) {
      ll expected = minimum ? LLONG_MAX : LLONG_MIN;
      for(auto [a, b] : lines) expected = minimum ? min(expected, a * x + b) : max(expected, a * x + b);
      assert(inc.query_monotone_inc(x) == expected);
      assert(dec.query_monotone_dec(-x) == cht.query(-x));
   }
   cht.clear();
   assert(cht.empty());
}

// Arbitrary-order official line_add_get_min cannot directly drive the monotone-slope CHT API.
// LineContainer and Li Chao use official wrappers; only CHT needs supplemental tests here.
int main() {
   mt19937 rng(20261103);
   rep(step, 100) {
      vector<pll> lines;
      rep(i, 40) lines.eb(int(rng() % 21) - 10, int(rng() % 41) - 20);
      sort(all(lines));
      check_lines<true>(lines);
      check_lines<false>(lines);
      reverse(all(lines));
      check_lines<true>(lines);
      check_lines<false>(lines);
   }

   check_lines<true>({{2, 0}, {2, 0}, {2, 3}, {2, -3}});
   check_lines<false>({{2, 0}, {2, 0}, {2, 3}, {2, -3}});
   check_lines<true>({{-1000000000, 1000000000}, {0, 0}, {1000000000, -1000000000}});
   check_lines<false>({{-1000000000, 1000000000}, {0, 0}, {1000000000, -1000000000}});
   puts("Hello World");
}
