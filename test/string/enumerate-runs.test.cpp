#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"
#include "test/template.hpp"
#include "src/string/Zalgorithm.hpp"
#include "src/string/enumerate-runs.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   string s;
   cin >> s;
   auto runs = enum_runs(vector<char>(all(s)));
   sort(all(runs));
   cout << runs.size() << '\n';
   for(auto [p, l, r] : runs) cout << p << ' ' << l << ' ' << r << '\n';
}
