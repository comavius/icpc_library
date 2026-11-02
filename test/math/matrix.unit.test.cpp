#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
struct F {
   int x;
   F(ll v = 0) : x((v % 7 + 7) % 7) {}
   F operator-() const { return F(-x); }
   F& operator+=(F b) { return *this = F(x + b.x); }
   F& operator-=(F b) { return *this = F(x - b.x); }
   F& operator*=(F b) { return *this = F(x * b.x); }
   F inv() const {
      F result = 1;
      rep(i, 5) result *= *this;
      return result;
   }
   friend F operator*(F a, F b) { return a *= b; }
   friend F operator/(F a, F b) { return a * b.inv(); }
};
#include "src/math/matrix.hpp"
int determinant(vector<vi> a) {
   int n = si(a), answer = 0;
   vi permutation(n);
   iota(all(permutation), 0);
   do {
      int term = 1, inv = 0;
      rep(i, n) {
         term = term * a[i][permutation[i]] % 7;
         rep(j, i + 1, n) inv += permutation[i] > permutation[j];
      }
      answer += (inv & 1) ? -term : term;
   } while(next_permutation(all(permutation)));
   return (answer % 7 + 7) % 7;
}
int main() {
   mt19937 rng(20261103);
   rep(step, 200) {
      int n = rng() % 5, m = rng() % 5, k = rng() % 5;
      M<ll> a(n, m), b(m, k);
      rep(i, n) rep(j, m) a[i][j] = int(rng() % 11) - 5;
      rep(i, m) rep(j, k) b[i][j] = int(rng() % 11) - 5;
      auto c = a * b;
      assert(c.n == n && c.m == k);
      rep(i, n) rep(j, k) {
         ll expected = 0;
         rep(t, m) expected += a[i][t] * b[t][j];
         assert(c[i][j] == expected);
      }
      auto copy = a;
      copy *= b;
      assert(copy.a == c.a && copy.m == k);
      assert((a + a - a).a == a.a);
      copy = a;
      copy += a;
      copy -= a;
      assert(copy.a == a.a);
      M<ll> square(3);
      rep(i, 3) rep(j, 3) square[i][j] = rng() % 3;
      auto repeated = M<ll>::I(3);
      rep(e, 6) {
         assert((square ^ e).a == repeated.a);
         auto p = square;
         p ^= e;
         assert(p.a == repeated.a);
         repeated *= square;
      }
      M<F> mat(n, m);
      rep(i, n) rep(j, m) mat[i][j] = rng() % 7;
      int rank = 0;
      rep(rmask, 1 << n) rep(cmask, 1 << m) if(popcount(unsigned(rmask)) == popcount(unsigned(cmask))) {
         vector<vi> minor;
         rep(i, n) if(rmask >> i & 1) {
            vi row;
            rep(j, m) if(cmask >> j & 1) row.eb(mat[i][j].x);
            minor.eb(row);
         }
         if(determinant(minor)) chmax(rank, popcount(unsigned(rmask)));
      }
      auto reduced = mat;
      auto [actual, det] = GaussElimination(reduced);
      assert(actual == rank);
      if(n == m) {
         vector<vi> raw(n, vi(n));
         rep(i, n) rep(j, n) raw[i][j] = mat[i][j].x;
         assert(det.x == determinant(raw));
      }
   }
   rep(step, 200) {
      int n = rng() % 4, m = rng() % 4;
      M<F> a(n, m);
      vector<F> b(n);
      rep(i, n) {
         b[i] = rng() % 7;
         rep(j, m) a[i][j] = rng() % 7;
      }
      set<vi> expected;
      int limit = 1;
      rep(i, m) limit *= 7;
      rep(mask, limit) {
         int value = mask;
         vi x(m);
         rep(j, m) {
            x[j] = value % 7;
            value /= 7;
         }
         bool ok = true;
         rep(i, n) {
            int sum = 0;
            rep(j, m) sum += a[i][j].x * x[j];
            if(sum % 7 != b[i].x) ok = false;
         }
         if(ok) expected.insert(x);
      }
      auto solutions = LinearEquation(a, b);
      set<vi> actual;
      if(!solutions.empty()) {
         limit = 1;
         rep(i, si(solutions) - 1) limit *= 7;
         rep(mask, limit) {
            auto x = solutions[0];
            int value = mask;
            rep(i, 1, si(solutions)) {
               int coeff = value % 7;
               value /= 7;
               rep(j, m) x[j] += solutions[i][j] * F(coeff);
            }
            vi raw;
            for(auto v : x) raw.eb(v.x);
            actual.insert(raw);
         }
      }
      assert(actual == expected);
   }
   puts("Hello World");
}
