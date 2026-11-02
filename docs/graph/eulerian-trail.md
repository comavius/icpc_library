---
title: オイラー路
documentation_of: //src/graph/eulerian-trail.hpp
---

`eulerian_path(edges,start,directed=false)` は指定した始点から全辺を一度ずつ使う辺列を返す。不存在なら空列。自己ループ・多重辺にも対応する。辺のidxは呼出側の識別子を保持する。空の辺列は空結果であり、不存在とは辺数を見て区別する。

主検証はLibrary Checkerの有向/無向Euler路。自前テストは公式問題側が選ぶ始点と違い、APIへ不適切な始点を直接渡す境界だけを補う。
