#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/FPS/FFT.hpp"
#include "src/FPS/poly.hpp"
#include "src/FPS/linear-recurrence.hpp"
#include "src/FPS/relaxed-convolution.hpp"
int main() {
   // kth_term fixes q[0]=1 and a proper numerator: test only other rational-function contracts here.
   for(ll constant : {2LL, 3LL}) {
      fps q(vm{constant, -constant}), p(vm{6, 4, 7});
      vm expected(30);
      mint inv = mint(constant).inv();
      rep(i, 30) expected[i] = (p.freq(i) + (i ? expected[i - 1] * constant : mint(0))) * inv;
      rep(i, 30) assert(LinearRecurrence(i, q, p).x == expected[i].x);
   }
   assert(LinearRecurrence(1000000000000000000LL, fps(vm{2, -2}), fps(vm{6})).x == 3);
   assert(LinearRecurrence(0, fps(vm{1}), fps()).x == 0);
   relaxed_multiplication stream;
   assert(stream.f.empty() && stream.g.empty() && stream.h.empty());
   puts("Hello World");
}
