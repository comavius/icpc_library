#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/BIT.hpp"
#include "src/data-structure/FastSet.hpp"

int main() {
   // point_add_range_sum has nonnegative updates; predecessor_problem uses only 0/1 weights.
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
                  if(sum >= w) {
                     expected = j + 1;
                     break;
                  }
               }
               assert(positive.lower_bound(w) == expected);
            }
         }
      }
   }
   // predecessor_problem requires n>=1; all ordinary FS operations use its official cases.
   FS fs(0);
   assert(fs.next(-1) == 0 && fs.prev(0) == -1);
   puts("Hello World");
}
