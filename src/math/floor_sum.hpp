// x_i=floor((a*i+b)/c), i=0,1,..n-1
// a,b>=0, c>0
ll floor_sum(ll n, ll a, ll b, ll c) {
   if(n == 0) return 0;
   i128 res = 0;
   res += i128(n) * (n - 1) / 2 * (a / c);
   a %= c;
   res += i128(n) * (b / c);
   b %= c;
   if(a == 0) return res;
   ll top = (i128(a) * (n - 1) + b) / c;
   res += i128(top) * n;
   if(top) res -= i128(floor_sum(top, c, c - b - 1, a)) + top;
   return res;
}
