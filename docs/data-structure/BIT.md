---
title: BIT (Fenwick Tree)
documentation_of: //src/data-structure/BIT.hpp
---

- 参考実装：[AC Library](https://github.com/atcoder/ac-library/blob/8250de484ae0ab597391db58040a602e0dc1a419/atcoder/fenwicktree.hpp)

## 使い方

1 点加算・区間和ができるデータ構造

- `BIT(ll n)`：長さ $n$ の配列を作る
- `void add(ll i, ll x)`：`A[i] += x` を行う
- `ll sum(ll r)`：`sum(A[:r])` を求める
- `ll sum(ll l, ll r)`：`sum(A[l:r])` を求める
- `int lower_bound(ll w)`：`sum(i) >= w` となる最小の正の prefix 長 $i$ を返す。見つからない場合は $n+1$。$n\ge1$ かつ全要素が非負であること。$w\le0$ の返却値は $1$。

添字と区間は $0\le i<n$、$0\le l\le r\le n$。空配列でも空区間の和は $0$。更新値と合計は符号付き64bitに収まる範囲で使う。

計算量 $O(\log n)$ / クエリ
