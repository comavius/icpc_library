#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C"
#include "test/template.hpp"
#include "src/data-structure/Skew-Heap.hpp"

int main() {
   cin.tie(nullptr)->sync_with_stdio(false);
   using Heap = SkewHeap<ll, false>;
   Heap::P root = nullptr;
   string operation;
   while(cin >> operation && operation != "end") {
      if(operation == "insert") {
         ll key;
         cin >> key;
         root = Heap::push(root, key);
      } else {
         Heap::propagate(root);
         cout << root->key << '\n';
         auto old = root;
         root = Heap::pop(root);
         delete old;
      }
   }
   while(root) {
      auto old = root;
      root = Heap::pop(root);
      delete old;
   }
}
