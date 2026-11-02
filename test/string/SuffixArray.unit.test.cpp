#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/string/SuffixArray.hpp"
void check(const string& s) {
   vl expected(si(s)), lcp(max(0, si(s) - 1));
   iota(all(expected), 0);
   sort(all(expected), [&](int a, int b) { return s.substr(a) < s.substr(b); });
   rep(i, si(lcp)) {
      int a = expected[i], b = expected[i + 1];
      while(a + lcp[i] < si(s) && b + lcp[i] < si(s) && s[a + lcp[i]] == s[b + lcp[i]]) ++lcp[i];
   }
   auto [actual, common] = SA(s);
   assert(actual == expected && common == lcp);
}
int main() {
   for(string s : {"", "a", "aa", "banana", "abababab", "abcdef"}) check(s);
   rep(n, 10) rep(mask, 1 << n) {
      string s(n, 'a');
      rep(i, n) s[i] += mask >> i & 1;
      check(s);
   }
   check(string("\0\xff\0\x80\0", 5));
   mt19937 rng(20261103);
   rep(step, 1000) {
      string s(rng() % 100, 0);
      for(char& c : s) c = rng() % 256;
      check(s);
   }
   check(string(2000, 'a'));
   puts("Hello World");
}
