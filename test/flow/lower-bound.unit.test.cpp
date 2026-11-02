#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/flow/flow.hpp"
#include "src/flow/lower-upper-bound-flow.hpp"
#include "src/flow/mcf.hpp"
#include "src/flow/bipartite-matching.hpp"
int main() {
   // No matching official lower/upper-bound flow task. Exhaust tiny DAG terminal flows.
   mt19937 rng(20261103);
   rep(step, 300) {
      int n = 2 + rng() % 4, m = rng() % 7;
      vector<array<int, 4>> edges;
      rep(i, m) {
         int u = rng() % (n - 1), v = u + 1 + rng() % (n - u - 1), hi = rng() % 3, lo = rng() % (hi + 1);
         edges.push_back({u, v, lo, hi});
      }
      int low = INT_MAX, high = -1;
      vi balance(n);
      auto enumerate = [&](auto&& self, int i) -> void {
         if(i == m) {
            rep(v, 1, n - 1) if(balance[v]) return;
            int value = -balance[0];
            if(value < 0 || balance[n - 1] != value) return;
            chmin(low, value);
            chmax(high, value);
            return;
         }
         auto [u, v, l, h] = edges[i];
         rep(f, l, h + 1) {
            balance[u] -= f;
            balance[v] += f;
            self(self, i + 1);
            balance[u] += f;
            balance[v] -= f;
         }
      };
      enumerate(enumerate, 0);
      lrFlow<ll> minimum(n), maximum(n), feasible(n);
      for(auto [u, v, l, h] : edges) {
         minimum.add_edge(u, v, l, h);
         maximum.add_edge(u, v, l, h);
         feasible.add_edge(u, v, l, h);
      }
      assert(feasible.can_flow(0, n - 1) == (high >= 0));
      assert(maximum.max_flow(0, n - 1) == high);
      assert(minimum.min_flow(0, n - 1) == (high < 0 ? -1 : low));
   }
   lrFlow<ll> cycle(2);
   cycle.add_edge(0, 1, 1, 2);
   cycle.add_edge(1, 0, 1, 2);
   assert(cycle.can_flow());
   // AOJ capacities are narrower; test the ll API and repeated calls directly.
   Dinic<ll> large(2);
   large.add_edge(0, 1, 1LL << 50);
   assert(large.max_flow(0, 1) == (1LL << 50));
   MCF negative(3);
   negative.add(0, 1, 2, -3);
   negative.add(1, 2, 2, 1);
   negative.add(0, 2, 1, 5);
   assert(negative.mcf(0, 2, 1) == -2);
   assert(negative.mcf(0, 2, 1) == -2);
   assert(negative.mcf(0, 2, 1) == 5);
   assert(negative.mcf(0, 2, 1) == -1);
   MCF unreachable(3);
   rep(i, 1, 6) unreachable.add(0, 1, 1, i);
   assert(unreachable.mcf(0, 1, 5) == 15);
   Bimatch empty(0, 0);
   assert(empty.match() == 0);
   puts("Hello World");
}
