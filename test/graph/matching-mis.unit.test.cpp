#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/graph/max_matching.hpp"
#include "src/graph/maximum-independent-set.hpp"

void check(const vector<vi>& g) {
   int n = si(g);
   vector<unsigned> adjacent(n);
   rep(i, n) for(int j : g[i]) adjacent[i] |= 1U << j;
   vector<int> dp(1 << n, -1);
   auto matching = [&](auto&& self, unsigned mask) -> int {
      if(!mask) return 0;
      int& result = dp[mask];
      if(result >= 0) return result;
      int i = countr_zero(mask);
      mask ^= 1U << i;
      result = self(self, mask);
      rep(j, n) if((mask & adjacent[i]) >> j & 1) chmax(result, 1 + self(self, mask ^ (1U << j)));
      return result;
   };
   auto edges = Matching(g).max_match();
   assert(si(edges) == matching(matching, (1U << n) - 1));
   vector<bool> used(n);
   for(auto [u, v] : edges) {
      assert(u >= 0 && u < n && v >= 0 && v < n && u != v);
      assert(!used[u] && !used[v] && (adjacent[u] >> v & 1));
      used[u] = used[v] = true;
   }
   int optimum = 0;
   rep(mask, 1U << n) {
      bool independent = true;
      rep(i, n) if((mask >> i & 1) && (mask & adjacent[i])) { independent = false; break; }
      if(independent) chmax(optimum, popcount(unsigned(mask)));
   }
   auto vertices = maximum_independent_set(g);
   assert((vertices >> n) == 0 && popcount(vertices) == optimum);
   rep(i, n) if(vertices >> i & 1) assert(!(vertices & adjacent[i]));
}

int main() {
   // Every labelled simple graph up to five vertices, including disconnected cases.
   rep(n, 6) {
      vector<pii> candidates;
      rep(u, n) rep(v, u + 1, n) candidates.eb(u, v);
      rep(mask, 1U << si(candidates)) {
         vector<vi> g(n);
         rep(e, si(candidates)) if(mask >> e & 1) {
            auto [u, v] = candidates[e];
            g[u].eb(v); g[v].eb(u);
         }
         check(g);
      }
   }
   mt19937 rng(20261103);
   rep(step, 500) {
      int n = 6 + rng() % 7, density = rng() % 101;
      vector<vi> g(n);
      rep(u, n) rep(v, u + 1, n) if(int(rng() % 100) < density) {
         g[u].eb(v); g[v].eb(u);
         if(step % 7 == 0) { g[u].eb(v); g[v].eb(u); }
      }
      check(g);
   }
   // Two odd cycles joined through their vertices, with leaves and nested contractions.
   vector<vi> blossom(10);
   for(auto [u, v] : vector<pii>{{0,1},{1,2},{2,0},{2,3},{3,4},{4,5},{5,6},{6,2},{1,7},{4,8},{6,9}}) {
      blossom[u].eb(v); blossom[v].eb(u);
   }
   check(blossom);
   vector<vi> empty(63), complete(63);
   rep(u, 63) rep(v, 63) if(u != v) complete[u].eb(v);
   assert(popcount(maximum_independent_set(empty)) == 63);
   assert(popcount(maximum_independent_set(complete)) == 1);
   assert(Matching(complete).max_match().size() == 31);
   puts("Hello World");
}
