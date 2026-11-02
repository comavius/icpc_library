#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/graph/eulerian-trail.hpp"
int main() {
   // Official tasks choose a valid start, while this API accepts an explicit start vertex.
   assert(eulerian_path({{0, 1, 0}}, 1, true).empty());
   assert(eulerian_path({{0, 1, 0}}, 5, false).empty());
   assert(eulerian_path({}, 0).empty());
   puts("Hello World");
}
