#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/BIT.hpp"
#include "src/data-structure/FastSet.hpp"

int main() {
   mt19937 rng(20261103);
   BIT empty(0);
   assert(empty.sum(0) == 0 && empty.sum(0, 0) == 0);
   for(int n : {1, 2, 3, 63, 64, 65, 127, 128, 129}) {
      BIT bit(n);
      vl a(n);
      rep(step, 1000) {
         int i = rng() % n;
         ll x = static_cast<ll>(rng() % 2000000001) - 1000000000;
         a[i] += x;
         bit.add(i, x);
         int l = rng() % (n + 1), r = rng() % (n + 1);
         if(l > r) swap(l, r);
         assert(bit.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
         assert(bit.sum(r) == accumulate(a.begin(), a.begin() + r, 0LL));
         assert(bit.sum(0, n) == accumulate(all(a), 0LL));
         assert(bit.sum(l, l) == 0);
      }
      BIT positive(n);
      fill(all(a), 0);
      rep(step, 100) {
         int i = rng() % n;
         ll x = rng() % 4;
         a[i] += x;
         positive.add(i, x);
         ll total = accumulate(all(a), 0LL);
         for(ll w : {-1LL, 0LL, 1LL, total, total + 1}) {
            int expected = 1;
            ll prefix = a[0];
            while(expected <= n && prefix < w) {
               if(expected < n) prefix += a[expected];
               ++expected;
            }
            assert(positive.lower_bound(w) == expected);
         }
         ll prefix = 0;
         for(ll value : a) {
            prefix += value;
            for(ll w : {prefix, prefix + 1}) {
               ll sum = 0;
               int expected = n + 1;
               rep(j, n) {
                  sum += a[j];
                  if(sum >= w) { expected = j + 1; break; }
               }
               assert(positive.lower_bound(w) == expected);
            }
         }
      }
   }
   for(int n : {0, 1, 2, 63, 64, 65, 4095, 4096, 4097}) {
      FS fs(n);
      set<ll> expected;
      auto check = [&](int i) {
         if(i >= 0 && i < n) assert(fs[i] == expected.contains(i));
         auto next = expected.upper_bound(i);
         assert(fs.next(i) == (next == expected.end() ? n : *next));
         auto prev = expected.lower_bound(i);
         assert(fs.prev(i) == (prev == expected.begin() ? -1 : *std::prev(prev)));
      };
      // next accepts -1..n-1; prev accepts 0..n, with strict inequalities.
      assert(fs.next(-1) == n && fs.prev(n) == -1);
      rep(i, n) { check(i); fs.set(i); fs.set(i); expected.insert(i); }
      rep(i, n) check(i);
      assert(fs.next(-1) == (n ? 0 : n));
      assert(fs.prev(n) == n - 1);
      rep(i, n) { fs.erase(i); fs.erase(i); expected.erase(i); check(i); }
      rep(step, n ? 5000 : 0) {
         int i = rng() % n;
         if(rng() & 1) { fs.set(i); expected.insert(i); }
         else { fs.erase(i); expected.erase(i); }
         check(i);
         check(rng() % n);
         assert(fs.next(-1) == (expected.empty() ? n : *expected.begin()));
         assert(fs.prev(n) == (expected.empty() ? -1 : *expected.rbegin()));
      }
   }
   puts("Hello World");
}
