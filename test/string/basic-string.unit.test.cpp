#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/string/KMP.hpp"
#include "src/string/Manacher.hpp"
#include "src/string/Zalgorithm.hpp"
#include "src/string/RollingHash.hpp"

template<class T> void check_z(const vector<T>& s) {
   vi expected(si(s));
   rep(i, si(s)) while(i + expected[i] < si(s) && s[expected[i]] == s[i + expected[i]])++ expected[i];
   assert(z_algorithm(s) == expected);
}

void check(const string& s) {
   int n = si(s);
   check_z(vector<char>(all(s)));
   vl prefix(n), radius(n);
   rep(i, n) {
      rep(length, 1, i + 1) {
         if(s.substr(0, length) == s.substr(i + 1 - length, length)) prefix[i] = length;
      }
      radius[i] = 1;
      while(i - radius[i] >= 0 && i + radius[i] < n && s[i - radius[i]] == s[i + radius[i]]) ++radius[i];
   }
   assert(KMP(s) == prefix);
   assert(manacher(s) == radius);
   RH rh(s);
   rep(l, n + 1) rep(end, l, n + 1) {
      i128 expected = 0;
      rep(k, l, end) expected = (expected * r + static_cast<unsigned char>(s[k])) % mod;
      assert(rh.get(l, end) == expected);
   }
   rep(i, n + 1) rep(j, n + 1) {
      int expected = 0;
      while(i + expected < n && j + expected < n && s[i + expected] == s[j + expected]) ++expected;
      assert(rh.lcp(i, j) == expected);
   }
}

int main() {
   // Official tasks omit empty/NUL strings, raw prefix/radius/hash arrays and integer-vector Z.
   for(string s : {"", "a", "aaaa", "abababa"}) check(s);
   check(string("\0a\0$\177\0", 6));
   check_z(vector<ll>{});
   check_z(vector<ll>{LLONG_MIN, LLONG_MAX, LLONG_MIN});
   check_z(vector<ll>{-1, 0, -1, 0, -1});
   puts("Hello World");
}
