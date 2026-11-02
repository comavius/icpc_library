#include "test/template.hpp"
#include "src/graph/eulerian-trail.hpp"
void solve(bool directed) {
   cin.tie(nullptr)->sync_with_stdio(false);
   int cases;
   cin >> cases;
   while(cases--) {
      int n, m;
      cin >> n >> m;
      vector<edge> edges(m);
      vi degree(n);
      rep(i, m) {
         auto& e = edges[i];
         cin >> e.x >> e.y;
         e.idx = i;
         ++degree[e.x];
         degree[e.y] += directed ? -1 : 1;
      }
      int start = m ? edges[0].x : 0;
      rep(i, n) if(directed ? degree[i] == 1 : (degree[i] & 1)) {
         start = i;
         break;
      }
      auto trail = eulerian_path(edges, start, directed);
      if(si(trail) != m) {
         cout << "No\n";
         continue;
      }
      cout << "Yes\n" << start;
      for(auto e : trail) cout << ' ' << e.y;
      cout << '\n';
      for(auto e : trail) cout << e.idx << ' ';
      cout << '\n';
   }
}
