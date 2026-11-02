#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/template/rnd.hpp"
#include "src/misc/clock.hpp"
#include "src/data-structure/BIT.hpp"

int main() {
   vl values;
   rep(i, 4) values.eb(i);
   assert(si(values) == 4 && sz(values) == 4);
   ll total = 0;
   fore(x, values) total += x;
   assert(total == 6);
   per(i, 4, 0) assert(values[i] == i);
   ll x = 5;
   assert(chmin(x, 2) && x == 2);
   assert(!chmin(x, 3));
   assert(chmax(x, 7) && x == 7);
   assert(!chmax(x, 6));
   assert(i128(LLONG_MAX) * 2 > LLONG_MAX);
   BIT bit(4);
   rep(i, 4) bit.add(i, values[i]);
   assert(bit.sum(4) == 6);
   rep(_, 100) assert(rnd(-2, 3) >= -2 && rnd(-2, 3) < 3);
   auto v = rvi<int>(20, -5, 5);
   for(auto a : v) assert(-5 <= a && a < 5);
   auto unique_values = rvi<int>(10, -5, 5, true);
   sort(all(unique_values));
   rep(i, 10) assert(unique_values[i] == i - 5);
   rndshuf(values);
   sort(all(values));
   rep(i, 4) assert(values[i] == i);
   Timer timer;
   assert(timer.elapsed() >= 0);
   puts("Hello World");
}
