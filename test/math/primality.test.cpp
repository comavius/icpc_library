#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include "test/template.hpp"
#include "src/template/rnd.hpp"
#include "src/math/prime.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int q;
   cin >> q;
   while(q--) {
      ll n;
      cin >> n;
      cout << (is_prime(n) ? "Yes" : "No") << '\n';
   }
}
