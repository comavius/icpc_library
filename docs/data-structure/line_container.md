---
title: 任意順の直線追加
documentation_of: //src/data-structure/line_container.hpp
---

`LineContainer<ismin>` は `add(a,b)` で任意順に直線を追加し、`query(x)` で評価値の最小/最大を求める。既定は最小値、`false` は最大値。同じ傾き・切片も使用できる。交点は負数も含めて床除算される。

空構造への問い合わせは対象外。係数・xの絶対値10^9以下を想定し、評価値と交点計算の差分が符号付き64bitに収まる範囲で使う。
