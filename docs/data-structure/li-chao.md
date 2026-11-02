---
title: 座標圧縮Li Chao tree
documentation_of: //src/data-structure/li-chao.hpp
---

`lctree(xs)` は空でない問い合わせ座標を先に渡して構築する。重複座標も使用できる。`update(a,b)` は直線を全域に追加、`update_segment(l,r,a,b)` は半開区間 `[l,r)` に追加、`query(x)` は最小値を返す。問い合わせのxは構築時の座標に含まれること。

該当する直線がなければ `INFL`。係数・xの絶対値10^9以下を想定し、積・和が符号付き64bitに収まり、評価値が `INFL` 未満の範囲で使う。最大値のAPIはない。
