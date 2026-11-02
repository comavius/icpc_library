#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/segtree.hpp"
string concat(string a, string b) { return a + b; }
string empty_string() { return {}; }
int main() {
   // Official point_set_range_composite omits empty construction and boundary-search API.
   segtree<string, concat, empty_string> empty(0);
   assert(empty.all_prod().empty() && empty.prod(0, 0).empty());
   auto accept = [](string s) { return s.size() <= 2; };
   assert(empty.max_right(0, accept) == 0 && empty.min_left(0, accept) == 0);
   segtree<string, concat, empty_string> tree(vector<string>{"a", "bc", "d"});
   assert(tree.all_prod() == "abcd");
   assert(tree.max_right(1, accept) == 2);
   assert(tree.min_left(3, accept) == 2);
   tree.set(1, "X");
   assert(tree.prod(0, 3) == "aXd");
   puts("Hello World");
}
