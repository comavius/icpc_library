#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/string/SuffixArray.hpp"
// Official tasks expose SA and the LCP sum; check the raw LCP array here.
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
   // Official tasks expose SA or the LCP sum, not the complete n-1 LCP array.
   for(string s : {"", "a", "aa", "banana", "abababab"}) check(s);
   puts("Hello World");
}
