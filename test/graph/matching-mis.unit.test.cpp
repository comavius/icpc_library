#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/graph/max_matching.hpp"
#include "src/graph/maximum-independent-set.hpp"
int main() {
   // Official graph inputs are nonempty and simple. MIS official limit is below 63.
   assert(Matching(vector<vi>{}).max_match().empty());
   assert(maximum_independent_set({}) == 0);
   vector<vi> duplicated{{1, 1}, {0, 0, 2, 2}, {1, 1}};
   auto edges = Matching(duplicated).max_match();
   assert(edges.size() == 1);
   auto chosen = maximum_independent_set(duplicated);
   assert(chosen == 5);
   vector<vi> empty(63), complete(63);
   rep(i, 63) rep(j, 63) if(i != j) complete[i].eb(j);
   assert(popcount(maximum_independent_set(empty)) == 63);
   assert(popcount(maximum_independent_set(complete)) == 1);
   puts("Hello World");
}
