// (rem, mod)
pll crt(const vl& b, const vl& c) {
   int n = si(b);
   ll r = 0, m = 1;
   rep(i, n) {
      ll g, im, x;
      g = extgcd(m, c[i], im, x);
      i128 d = i128(b[i]) - r;
      if(d % g) return {0, -1};
      ll tmp = d / g * im % (c[i] / g);
      r += m * tmp;
      m *= c[i] / g;
   }
   r %= m;
   return {r < 0 ? r + m : r, m};
}