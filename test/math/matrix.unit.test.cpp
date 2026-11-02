#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/modint/modint.hpp"
#include "src/math/matrix.hpp"
int main() {
   // Official matrix_product checks entries, not the returned public dimension metadata.
   M<mint> a(2, 3), b(3, 4);
   auto c = a * b;
   assert(c.n == 2 && c.m == 4 && c.a.size() == 2 && c.a[0].size() == 4);
   a *= b;
   assert(a.m == 4);
   M<mint> empty;
   assert(empty.n == 0 && empty.m == 0 && empty.a.empty());
   assert(M<mint>::I(0).a.empty());
   puts("Hello World");
}
