#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/Skew-Heap.hpp"
#include "src/data-structure/hash_map.hpp"
#include "src/data-structure/pbds.hpp"

template<bool minimum> void heaps() {
   using H = SkewHeap<ll, minimum>;
   typename H::P roots[2]{};
   multiset<ll> values[2];
   mt19937 rng(20261103);
   rep(step, 10000) {
      int i = rng() % 2;
      ll x = int(rng() % 2001) - 1000;
      switch(rng() % 4) {
         case 0: roots[i] = H::push(roots[i], x, step); values[i].insert(x); break;
         case 1:
            if(roots[i]) {
               H::propagate(roots[i]);
               auto expected = minimum ? values[i].begin() : prev(values[i].end());
               assert(roots[i]->key == *expected);
               auto old = roots[i]; roots[i] = H::pop(old); delete old;
               values[i].erase(expected);
            }
            break;
         case 2:
            if(roots[i]) {
               H::apply(roots[i], x);
               multiset<ll> updated;
               for(ll v : values[i]) updated.insert(v + x);
               values[i] = move(updated);
            }
            break;
         case 3:
            roots[i] = H::meld(roots[i], roots[1-i]); roots[1-i] = nullptr;
            values[i].merge(values[1-i]);
            break;
      }
      rep(j, 2) {
         assert(bool(roots[j]) == !values[j].empty());
         if(roots[j]) {
            H::propagate(roots[j]);
            assert(roots[j]->key == (minimum ? *values[j].begin() : *values[j].rbegin()));
         }
      }
   }
   rep(i, 2) while(roots[i]) { auto old = roots[i]; roots[i] = H::pop(old); delete old; }
}

int main() {
   heaps<true>(); heaps<false>();
   hash_map<ll,ll> table;
   map<ll,ll> expected;
   for(ll key : {LLONG_MIN, -1LL, 0LL, 1LL, LLONG_MAX}) table[key] = expected[key] = key;
   mt19937_64 rng(20261103);
   rep(step, 10000) {
      ll key = int(rng() % 201) - 100;
      if(rng() % 3) { ll value = rng() % 1000000000; table[key] = expected[key] = value; }
      else { table.erase(key); expected.erase(key); }
      assert(table.size() == expected.size());
      for(auto [k,v] : expected) assert(table.find(k) != table.end() && table.find(k)->second == v);
   }
   hash_map<int,int> int_keys; int_keys[0] = 7; assert(int_keys[0] == 7);
   PQ<int> queue;
   auto handle = queue.push(5); queue.push(3); queue.modify(handle, 1);
   assert(queue.top() == 1); queue.pop(); assert(queue.top() == 3);
   PQ<int> other; other.push(-2); queue.join(other);
   assert(other.empty() && queue.top() == -2);
   Trie trie;
   for(string s : {"aa","ab","abc","b"}) trie.insert(s);
   assert(!trie.insert("ab").second);
   auto [first,last] = trie.prefix_range(string("ab"));
   vector<string> words(first,last);
   assert((words == vector<string>{"ab","abc"}));
   trie.erase("ab"); assert(trie.find("ab") == trie.end());
   ordered_set ordered;
   set<int> standard;
   rep(step, 1000) {
      int key = int(rng() % 201) - 100;
      if(rng() & 1) { ordered.insert(key); standard.insert(key); }
      else { ordered.erase(key); standard.erase(key); }
      assert(ordered.size() == standard.size());
      assert(ordered.order_of_key(key) == size_t(distance(standard.begin(), standard.lower_bound(key))));
      int index = 0;
      for(int value : standard) assert(*ordered.find_by_order(index++) == value);
      assert(ordered.find_by_order(standard.size()) == ordered.end());
   }
   rope<char> text("abc");
   text.insert(1,"XY"); text.erase(3,1);
   assert(string(text.begin(),text.end()) == "aXYc");
   auto middle = text.substr(1,2);
   assert(string(middle.begin(),middle.end()) == "XY");
   puts("Hello World");
}
