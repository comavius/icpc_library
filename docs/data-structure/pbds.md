---
title: GNUコンテナのエイリアス
documentation_of: //src/data-structure/pbds.hpp
---

GNU libstdc++の拡張を使う。移植可能な標準コンテナではない。

- `PQ<T>` は `greater<T>` による最小ヒープ。push/pop/top、handleによるmodify、joinを使用できる。joinは結合元を空にする。
- `Trie` は既定のstring access traitsを使う小文字英字の文字列集合。非空文字列の挿入・削除・探索と `prefix_range` を検証している。
- `ordered_set` はintの集合。重複は保持しない。`order_of_key(x)` はx未満の要素数、`find_by_order(k)` は0始まりのk番目のiterator。範囲外ならend。
- `rope<char>` は文字列の挿入・削除・部分列を扱うGNU rope。
