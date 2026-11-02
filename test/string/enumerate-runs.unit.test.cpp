#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/string/Zalgorithm.hpp"
#include "src/string/enumerate-runs.hpp"
void check(const vl& s) {
   vector<array<int, 3>> expected;
   int n = si(s);
   rep(l, n) rep(r, l + 2, n + 1) {
      int period = 0;
      rep(p, 1, (r - l) / 2 + 1) {
         bool valid = true;
         rep(i, l + p, r) if(s[i] != s[i - p]) valid = false;
         if(valid) {
            period = p;
            break;
         }
      }
      if(!period) continue;
      if(l && s[l - 1] == s[l + period - 1]) continue;
      if(r < n && s[r] == s[r - period]) continue;
      expected.push_back({period, l, r});
   }
   auto actual = enum_runs(s);
   sort(all(actual));
   sort(all(expected));
   assert(actual == expected);
}
int main() {
   for(int n = 0, count = 1; n <= 8; ++n, count *= 3) rep(mask, count) {
         int k = mask;
         vl s(n);
         for(auto& x : s) {
            x = k % 3 - 1;
            k /= 3;
         }
         check(s);
      }
   check(vl(60, LLONG_MAX));
   check({LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MAX});
   mt19937 rng(20261103);
   rep(step, 1000) {
      vl s(rng() % 35);
      for(auto& x : s) x = rng() % 5;
      check(s);
   }
   puts("Hello World");
}
