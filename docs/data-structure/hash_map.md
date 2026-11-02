---
title: GNU hash table
documentation_of: //src/data-structure/hash_map.hpp
---

`hash_map<Key,Value>` はGNU PBDSの `gp_hash_table` に整数向けの `chash` を与えるエイリアス。GNU libstdc++が必要。キーは `int` や `ll` の整数を想定し、0、負数、llの上下限も検証する。文字列キー用のハッシュではない。

`operator[]` の挿入/更新、`find`、`erase`、`size` を標準mapと比較するテストがある。
