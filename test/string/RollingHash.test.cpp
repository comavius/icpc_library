#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "test/template.hpp"
#include "src/string/RollingHash.hpp"

int main() {
   cin.tie(0)->sync_with_stdio(0);
   string S;
   cin >> S;
   RH rh(S);
   const ll N = sz(S);
   rep(i, 0, N) cout << rh.lcp(0, i) << " \n"[i + 1 == N];
}
