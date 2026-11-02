#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#include "src/data-structure/Skew-Heap.hpp"
#include "src/data-structure/hash_map.hpp"
#include "src/data-structure/pbds.hpp"

// Official priority queue cannot exercise lazy additions/meld histories; retain this mixed-operation check.
template<bool minimum> void heaps() {
   using H = SkewHeap<ll, minimum>;
   typename H::P roots[2]{};
   multiset<ll> values[2];
   mt19937 rng(20261103);
   rep(step, 10000) {
      int i = rng() % 2;
      ll x = int(rng() % 2001) - 1000;
      switch(rng() % 4) {
         case 0:
            roots[i] = H::push(roots[i], x, step);
            values[i].insert(x);
            break;
         case 1:
            if(roots[i]) {
               H::propagate(roots[i]);
               auto expected = minimum ? values[i].begin() : prev(values[i].end());
               assert(roots[i]->key == *expected);
               auto old = roots[i];
               roots[i] = H::pop(old);
               delete old;
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
            roots[i] = H::meld(roots[i], roots[1 - i]);
            roots[1 - i] = nullptr;
            values[i].merge(values[1 - i]);
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
   rep(i, 2) while(roots[i]) {
      auto old = roots[i];
      roots[i] = H::pop(old);
      delete old;
   }
}

int main() {
   heaps<true>();
   heaps<false>();
   hash_map<ll, ll> table;
   map<ll, ll> expected;
   for(ll key : {LLONG_MIN, -1LL, 0LL, 1LL, LLONG_MAX}) table[key] = expected[key] = key;
   // associative_array omits deletion and negative/ll-limit keys.
   for(auto [key, value] : expected) assert(table[key] == value);
   for(auto [key, value] : expected) {
      table.erase(key);
      assert(table.find(key) == table.end());
   }
   assert(table.empty());
   mt19937_64 rng(20261103);
   hash_map<int, int> int_keys;
   int_keys[0] = 7;
   assert(int_keys[0] == 7);
   PQ<int> queue;
   auto handle = queue.push(5);
   queue.push(3);
   queue.modify(handle, 1);
   assert(queue.top() == 1);
   queue.pop();
   assert(queue.top() == 3);
   PQ<int> other;
   other.push(-2);
   queue.join(other);
   assert(other.empty() && queue.top() == -2);
   Trie trie;
   for(string s : {"aa", "ab", "abc", "b"}) trie.insert(s);
   assert(!trie.insert("ab").second);
   auto [first, last] = trie.prefix_range(string("ab"));
   vector<string> words(first, last);
   assert((words == vector<string>{"ab", "abc"}));
   trie.erase("ab");
   assert(trie.find("ab") == trie.end());
   // predecessor_problem uses only nonnegative bounded keys; retain signed bounds and duplicate semantics.
   ordered_set ordered;
   for(int x : {INT_MIN, -1, 0, INT_MAX}) ordered.insert(x);
   ordered.insert(-1);
   assert(ordered.size() == 4);
   assert(ordered.order_of_key(0) == 2 && *ordered.find_by_order(0) == INT_MIN);
   assert(ordered.find_by_order(4) == ordered.end());
   rope<char> text("abc");
   text.insert(1, "XY");
   text.erase(3, 1);
   assert(string(text.begin(), text.end()) == "aXYc");
   auto middle = text.substr(1, 2);
   assert(string(middle.begin(), middle.end()) == "XY");
   puts("Hello World");
}
