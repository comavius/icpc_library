---
title: 連の列挙
documentation_of: //src/string/enumerate-runs.hpp
---

`enum_runs(vector<T>)` は `(最小周期, l, r)` の列を返す。区間は `[l,r)`、長さは周期の2倍以上で、同じ周期のまま左右に延長できない極大区間。重複区間は返さない。空列・長さ1は空結果。要素は等値比較できればよく、Z算法に依存する。結果はl,r順であり、周期順が必要なら呼出側でsortする。
