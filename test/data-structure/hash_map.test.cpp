#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "test/template.hpp"
#include "src/data-structure/hash_map.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int q;
   cin >> q;
   hash_map<ll, ll> table;
   while(q--) {
      int t;
      ll k, v;
      cin >> t >> k;
      if(!t) {
         cin >> v;
         table[k] = v;
      } else cout << table[k] << '\n';
   }
}
