#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/string/KMP.hpp"
#include "src/string/Manacher.hpp"
#include "src/string/Zalgorithm.hpp"
#include "src/string/RollingHash.hpp"

template<class T> void check_z(const vector<T>& s) {
   vi expected(si(s));
   rep(i, si(s)) while(i + expected[i] < si(s) && s[expected[i]] == s[i + expected[i]]) ++expected[i];
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
   // Complete enumeration covers empty, identical, periodic and overlapping strings.
   for(int n = 0, count = 1; n <= 7; ++n, count *= 3) {
      rep(mask, count) {
         int value = mask;
         string s(n, 'a');
         for(char& c : s) { c += value % 3; value /= 3; }
         check(s);
         string separated(1, '$');
         for(char c : s) { separated += c; separated += '$'; }
         auto radii = manacher(separated);
         rep(center, n + 1) {
            int length = 0;
            while(center - length - 1 >= 0 && center + length < n && s[center - length - 1] == s[center + length]) ++length;
            assert(radii[2 * center] - 1 == 2 * length);
         }
      }
   }
   check(string("\0a\0$\177\0", 6));
   check("abababababababab");
   check(string(64, 'a'));
   mt19937 rng(20261103);
   rep(step, 200) {
      vector<ll> a(rng() % 65);
      for(auto& x : a) x = static_cast<ll>(rng() % 7) - 3;
      check_z(a);
   }
   check_z(vector<ll>{LLONG_MIN, LLONG_MAX, LLONG_MIN});
   puts("Hello World");
}
