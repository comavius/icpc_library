#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
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
      auto factors = factor(n);
      sort(all(factors));
      cout << factors.size();
      for(ll p : factors) cout << ' ' << p;
      cout << '\n';
   }
}
