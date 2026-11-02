---
title: Barrett Reduction
documentation_of: //src/modint/BarrettReduction.hpp
---
- 参考実装：[AC Library](https://github.com/atcoder/ac-library/blob/master/atcoder/internal_math.hpp)

同じ mod でたくさん計算するとき，剰余算を掛け算に変換して高速化する．

## 使い方

- `Barret br(mod)`：Barrett Reduction を準備する．
    - 制約：`1 <= mod < 2^32`。法1の結果は0。
- `u64 br.mul(u64 a, u64 b)`：`a * b % mod` を計算する．
    - 制約：`a * b < 2^64`

同ヘッダのmintは法998244353用。累乗の指数は非負、逆元・除算の入力は非零とする。法0や逆元のない入力は対象外で、競技用実装に検査コードは追加しない。

## 仕組み

- 整数部 64 bit，小数部 64 bit の固定小数点数で商を計算する．
- `im` には `1.0 / mod` の小数部 64 bit が書かれている．
- `u64 x = ((__uint128_t)a * im) >> 64;` で商を計算している．

## 余談

ジャッジが Ice Lake より前の Intel の CPU の場合，64 bit 除算が double 除算より 3 倍以上遅いことが知られている．  
あまりではなく商が欲しい場合，mod が固定ではない場合，もっと短く書きたい場合は，double 除算や long double 除算を書くと良い． 
