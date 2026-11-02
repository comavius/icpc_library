#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E"
#include "test/template.hpp"
#include "src/math/ExtGCD.hpp"
int main() {
   ll a,b,x,y;
   cin >> a >> b;
   extgcd(a,b,x,y);
   cout << x << ' ' << y << '\n';
}
