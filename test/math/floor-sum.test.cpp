#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
#include "test/template.hpp"
#include "src/math/floor_sum.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int t;
   cin >> t;
   while(t--) {
      ll n, m, a, b;
      cin >> n >> m >> a >> b;
      cout << floor_sum(n, a, b, m) << '\n';
   }
}
