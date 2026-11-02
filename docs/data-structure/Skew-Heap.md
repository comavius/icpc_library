---
title: 遅延加算付きSkew Heap
documentation_of: //src/data-structure/Skew-Heap.hpp
---

`SkewHeap<T,isMin>` は生のnodeポインタで根を管理する。既定は最小値、`false` は最大値。空ヒープは `nullptr`。

- `push(root,key,idx)` / `alloc(key,idx)` はnodeを確保する。
- `meld(a,b)` は2つのヒープを消費して結合した根を返す。共有nodeのあるヒープ同士を結合しない。
- `apply(root,delta)` は非空ヒープ全体に加算する。
- 最上位の値を読む前に `propagate(root)` を呼び、`root->key` を参照する。
- `pop(root)` は非空ヒープから根を外した新しい根を返す。外したnodeをdeleteする責任は呼出側にある。残りのnodeも使用後に解放する。

加算値・累積遅延値・キーが型Tの範囲に収まること。単体テストでは最小/最大の両設定でmultisetと照合し、空ヒープとのmeldも検証する。
