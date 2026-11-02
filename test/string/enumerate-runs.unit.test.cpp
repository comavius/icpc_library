#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/string/Zalgorithm.hpp"
#include "src/string/enumerate-runs.hpp"
int main() {
   // runenumerate accepts nonempty lowercase strings; cover empty and integer-vector API only.
   assert(enum_runs(vl{}).empty());
   assert(enum_runs(vl{LLONG_MAX}).empty());
   auto a = enum_runs(vl{LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MAX});
   assert((a == vector<array<int, 3>>{{2, 0, 4}}));
   auto b = enum_runs(vl{0, -1, 0, -1, 0});
   assert((b == vector<array<int, 3>>{{2, 0, 5}}));
   puts("Hello World");
}
