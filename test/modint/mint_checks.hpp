void check_mint() {
   auto normalize = [](ll x) {
      ll r = x % mod;
      return r < 0 ? r + mod : r;
   };
   auto power = [](ll a, ll n) {
      ll r = 1;
      while(n) {
         if(n & 1) r = i128(r) * a % mod;
         a = i128(a) * a % mod;
         n >>= 1;
      }
      return r;
   };
   for(ll x : {LLONG_MIN, -2LL * mod, -1LL, 0LL, 1LL, 1LL * mod - 1, 1LL * mod, LLONG_MAX}) {
      mint a(x);
      assert(a.x == normalize(x));
      assert((-a).x == normalize(-1LL * a.x));
      assert(a.pow(0).x == 1 && a.pow(1).x == a.x);
   }
   mt19937 rng(20261103);
   rep(i, 10000) {
      ll a = rng() % mod, b = rng() % mod;
      mint x(a), y(b);
      assert((x + y).x == (a + b) % mod && (x - y).x == normalize(a - b));
      assert((x * y).x == i128(a) * b % mod);
      assert((x += y).x == (a + b) % mod);
      x = a;
      assert((x -= y).x == normalize(a - b));
      x = a;
      assert((x *= y).x == i128(a) * b % mod);
      x = a;
      assert(x.pow(17).x == power(a, 17));
      if(b) {
         ll inverse = power(b, mod - 2);
         assert(y.inv().x == inverse && (x / y).x == i128(a) * inverse % mod);
         assert((x /= y).x == i128(a) * inverse % mod);
      }
   }
}
