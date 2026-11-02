---
title: Convex Hull Trick
documentation_of: //src/data-structure/cht.hpp
---

`CHT<isMin>` は直線 `add(a,b)` と `query(x)` を扱う。既定は最小値、`false` なら最大値。追加する傾きは、既存の傾きの最大値以上または最小値以下であること。同じ傾きは使用できる。`query_monotone_inc` / `query_monotone_dec` はそれぞれxが単調増加/減少する問い合わせで、不要になった直線を破棄する。

空構造への問い合わせは対象外。`empty()` と `clear()` が使える。検証の係数・xは絶対値10^9以下を想定し、評価値や差分が符号付き64bitに収まる範囲で使う。
