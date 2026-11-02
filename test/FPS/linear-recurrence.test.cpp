#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"
#include "src/FPS/linear-recurrence.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int d;
   ll k;
   cin >> d >> k;
   fps a(d), q(d + 1);
   q[0] = 1;
   for(auto& x : a.v) cin >> x.x;
   rep(i, 1, d + 1) {
      mint c;
      cin >> c.x;
      q[i] = -c;
   }
   cout << kitamasa(k, q, a).x << '\n';
}
