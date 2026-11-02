---
title: 最大独立集合
documentation_of: //src/graph/maximum-independent-set.hpp
---

`maximum_independent_set(g)` は無向グラフの最大独立集合を `unsigned long long` のビット集合で返す。立っているビットが選んだ頂点。隣接リストは両向きに入れ、頂点は `0..n-1`、頂点数は `0<=n<=63`。`1ULL<<n` を使うため64頂点は対象外。自己ループは対象外、重複辺は使用できる。

空グラフ・非連結グラフにも対応する。分岐探索なので大きな入力の計算時間はグラフの形に依存する。
