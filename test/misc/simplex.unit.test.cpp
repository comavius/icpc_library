#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/misc/simplex.hpp"

struct LP {
   vector<vector<double>> a;
   vector<double> b, c;
};
struct Fraction {
   ll numerator, denominator;
};
optional<Fraction> vertices(const LP& lp) {
   vector<array<ll, 3>> lines{{-1, 0, 0}, {0, -1, 0}};
   rep(i, si(lp.a))
       lines.push_back({static_cast<ll>(lp.a[i][0]), static_cast<ll>(lp.a[i][1]), static_cast<ll>(lp.b[i])});
   optional<Fraction> best;
   rep(i, si(lines)) rep(j, i + 1, si(lines)) {
      auto [a, b, c] = lines[i];
      auto [d, e, f] = lines[j];
      ll det = a * e - b * d, x = c * e - b * f, y = a * f - c * d;
      if(!det) continue;
      if(det < 0) det = -det, x = -x, y = -y;
      bool feasible = true;
      for(auto [u, v, w] : lines)
         if(i128(u) * x + i128(v) * y > i128(w) * det) feasible = false;
      if(!feasible) continue;
      ll objective = static_cast<ll>(lp.c[0]) * x + static_cast<ll>(lp.c[1]) * y;
      if(!best || i128(objective) * best->denominator > i128(best->numerator) * det) best = Fraction{objective, det};
   }
   return best;
}
template<class Solver> void validate(const LP& lp, const optional<Fraction>& expected, unsigned seed) {
   Solver solver(lp.a, lp.b, lp.c);
   auto require = [&](bool ok) {
      if(ok) return;
      cerr << "solver=" << typeid(Solver).name() << " input seed=" << seed << " EPS=" << solver.EPS
           << " shuffle columns:";
      for(int x : solver.shuffle_idx) cerr << ' ' << x;
      cerr << "\nA,b:\n";
      rep(i, si(lp.a)) {
         for(double x : lp.a[i]) cerr << x << ' ';
         cerr << " <= " << lp.b[i] << '\n';
      }
      cerr << "objective:";
      for(double x : lp.c) cerr << ' ' << x;
      cerr << endl;
      abort();
   };
   require(solver.infeasible == !expected.has_value());
   if(!expected) return;
   require(!solver.is_infty && solver.x.size() == lp.c.size());
   double optimum = double(expected->numerator) / expected->denominator;
   double tolerance = 100 * solver.EPS * (1 + abs(optimum));
   require(abs(solver.ans - optimum) <= tolerance);
   double objective = 0;
   rep(j, si(lp.c)) {
      require(solver.x[j] >= -tolerance);
      objective += lp.c[j] * solver.x[j];
   }
   require(abs(objective - optimum) <= tolerance);
   rep(i, si(lp.a)) {
      double value = 0;
      rep(j, si(lp.c)) value += lp.a[i][j] * solver.x[j];
      require(value <= lp.b[i] + tolerance);
   }
}
int main() {
   for(unsigned seed : {0U, 1U, 20261103U, 987654321U}) {
      mt19937 rng(seed);
      rep(step, 200) {
         LP lp{{{1, 0}, {0, 1}},
               {double(1 + rng() % 10), double(1 + rng() % 10)},
               {double(int(rng() % 11) - 5), double(int(rng() % 11) - 5)}};
         int additional = rng() % 7;
         rep(i, additional) {
            lp.a.push_back({double(int(rng() % 7) - 3), double(int(rng() % 7) - 3)});
            lp.b.push_back(double(int(rng() % 21) - 10));
         }
         auto expected = vertices(lp);
         validate<Simplex<double, 30, false>>(lp, expected, seed);
         validate<Simplex<double, 30, true>>(lp, expected, seed);
         if(expected) {
            auto dual = lp;
            Simplex<>::dual(dual.a, dual.b, dual.c);
            Fraction opposite{-expected->numerator, expected->denominator};
            validate<Simplex<double, 30, false>>(dual, opposite, seed);
            validate<Simplex<double, 30, true>>(dual, opposite, seed);
         }
      }
   }
   // Degeneracy, redundant constraints, multiple optima and a zero objective.
   for(auto lp : vector<LP>{{{{1, 0}, {0, 1}, {1, 1}, {2, 2}}, {1, 1, 1, 2}, {1, 1}},
                            {{{1, 0}, {0, 1}, {0, 0}}, {1, 1, 0}, {0, 0}},
                            {{{1, 0}, {-1, 0}, {0, 1}}, {1, -2, 1}, {1, 1}}}) {
      auto expected = vertices(lp);
      validate<Simplex<double, 20, false>>(lp, expected, 0);
      validate<Simplex<double, 40, true>>(lp, expected, 0);
   }
   Simplex<double, 30, false> unbounded({}, {}, {1});
   assert(unbounded.is_infty && !unbounded.infeasible);
   Simplex<double, 30, true> randomized_unbounded({}, {}, {1});
   assert(randomized_unbounded.is_infty && !randomized_unbounded.infeasible);
   Simplex<double, 30, false> nonpositive({}, {}, {-1});
   assert(!nonpositive.is_infty && !nonpositive.infeasible && nonpositive.ans == 0);
   Simplex<double, 30, true> infeasible({{1}, {-1}}, {1, -2}, {0});
   assert(infeasible.infeasible);
   Simplex<double, 30, false> empty({}, {}, {});
   assert(!empty.is_infty && !empty.infeasible && empty.x.empty() && empty.ans == 0);
   Simplex<double, 30, true> zero_variables({{}}, {-1}, {});
   assert(zero_variables.infeasible);
   // A coefficient below EPS can be ignored within the documented tolerance.
   Simplex<double, 30, false> tiny({{1}}, {1}, {0x1p-32});
   assert(!tiny.infeasible && !tiny.is_infty && abs(tiny.ans - 0x1p-32) < tiny.EPS);
   puts("Hello World");
}
