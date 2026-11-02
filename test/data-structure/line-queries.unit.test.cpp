#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/cht.hpp"
#include "src/data-structure/li-chao.hpp"
#include "src/data-structure/line_container.hpp"

template<bool minimum> void check_lines(vector<pll> lines) {
   CHT<minimum> cht, inc, dec;
   LineContainer<minimum> container;
   vector<pll> used;
   for(auto [a, b] : lines) {
      cht.add(a, b); inc.add(a, b); dec.add(a, b);
      container.add(a, b); used.eb(a, b);
      for(ll x : {-1000000000LL, -100LL, -7LL, -1LL, 0LL, 1LL, 8LL, 100LL, 1000000000LL}) {
         ll expected = minimum ? LLONG_MAX : LLONG_MIN;
         for(auto [slope, intercept] : used) {
            ll y = slope * x + intercept;
            expected = minimum ? min(expected, y) : max(expected, y);
         }
         assert(cht.query(x) == expected);
         assert(container.query(x) == expected);
      }
   }
   for(ll x = -100; x <= 100; ++x) {
      ll expected = minimum ? LLONG_MAX : LLONG_MIN;
      for(auto [a, b] : lines) expected = minimum ? min(expected, a * x + b) : max(expected, a * x + b);
      assert(inc.query_monotone_inc(x) == expected);
      assert(dec.query_monotone_dec(-x) == cht.query(-x));
   }
   cht.clear(); assert(cht.empty());
}

int main() {
   mt19937 rng(20261103);
   rep(step, 100) {
      vector<pll> lines;
      rep(i, 40) lines.eb(int(rng() % 21) - 10, int(rng() % 41) - 20);
      sort(all(lines));
      check_lines<true>(lines); check_lines<false>(lines);
      reverse(all(lines));
      check_lines<true>(lines); check_lines<false>(lines);
      // Arbitrary insertion order is a separate LineContainer contract.
      shuffle(all(lines), rng);
      LineContainer<true> lo; LineContainer<false> hi;
      vector<pll> used;
      for(auto [a, b] : lines) {
         lo.add(a, b); hi.add(a, b); used.eb(a, b);
         rep(x, -20, 21) {
            ll low = LLONG_MAX, high = LLONG_MIN;
            for(auto [slope, intercept] : used) {
               chmin(low, slope * x + intercept); chmax(high, slope * x + intercept);
            }
            assert(lo.query(x) == low && hi.query(x) == high);
         }
      }
      vl coordinates{-31, -20, -7, -1, 0, 0, 1, 9, 21, 32};
      lctree tree(coordinates);
      vl expected(si(coordinates), INFL);
      for(ll x : coordinates) assert(tree.query(x) == INFL);
      rep(i, 100) {
         ll a = int(rng() % 21) - 10, b = int(rng() % 41) - 20;
         ll l = int(rng() % 81) - 40, r = int(rng() % 81) - 40;
         if(l > r) swap(l, r);
         if(i % 3) tree.update_segment(l, r, a, b);
         else tree.update(a, b);
         rep(j, si(coordinates)) {
            ll x = coordinates[j];
            if(i % 3 == 0 || (l <= x && x < r)) chmin(expected[j], a * x + b);
            assert(tree.query(x) == expected[j]);
         }
      }
   }
   check_lines<true>({{2,0},{2,0},{2,3},{2,-3}});
   check_lines<false>({{2,0},{2,0},{2,3},{2,-3}});
   check_lines<true>({{-1000000000,1000000000},{0,0},{1000000000,-1000000000}});
   check_lines<false>({{-1000000000,1000000000},{0,0},{1000000000,-1000000000}});
   puts("Hello World");
}
