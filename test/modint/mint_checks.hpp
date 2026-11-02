// Official convolution covers ordinary modular arithmetic. Keep constructor,
// reference-returning compound operators and general inverse/power API boundaries.
void check_mint() {
   auto normalize = [](ll x) {
      x %= mod;
      return x < 0 ? x + mod : x;
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
   for(ll raw : {LLONG_MIN, -2LL * mod, -1LL, 0LL, 1LL, 1LL * mod, LLONG_MAX}) {
      mint a(raw);
      assert(a.x == normalize(raw));
      assert((-a).x == normalize(-1LL * a.x));
      assert(a.pow(0).x == 1 && a.pow(1).x == a.x);
   }
   for(ll a : {0LL, 1LL, 1LL * mod - 1})
      for(ll b : {0LL, 1LL, 1LL * mod - 1}) {
         mint x(a), y(b);
         assert(&(x += y) == &x);
         x = a;
         assert(&(x -= y) == &x);
         x = a;
         assert(&(x *= y) == &x);
         x = a;
         assert(x.pow(17).x == power(a, 17));
         if(b) {
            ll inverse = power(b, mod - 2);
            assert(y.inv().x == inverse);
            assert((x / y).x == i128(a) * inverse % mod);
            assert(&(x /= y) == &x);
         }
      }
}
