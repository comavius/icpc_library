#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "test/template.hpp"
#include "src/data-structure/pbds.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   int n, q;
   string s;
   cin >> n >> q >> s;
   ordered_set a;
   rep(i, n) if(s[i] == '1') a.insert(i);
   while(q--) {
      int t, k;
      cin >> t >> k;
      if(t == 0) a.insert(k);
      if(t == 1) a.erase(k);
      if(t == 2) cout << (a.find(k) != a.end()) << '\n';
      if(t == 3) {
         auto it = a.find_by_order(a.order_of_key(k));
         cout << (it == a.end() ? -1 : *it) << '\n';
      }
      if(t == 4) {
         int count = a.order_of_key(k + 1);
         cout << (count ? *a.find_by_order(count - 1) : -1) << '\n';
      }
   }
}
