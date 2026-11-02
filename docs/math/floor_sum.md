---
title: floor_sumとビット変換
documentation_of: //src/math/floor_sum.hpp
---

`floor_sum(n,a,b,c)` はi=0..n-1のfloor((a*i+b)/c)の和。n,a,bは非負、cは正、結果はllに収まること。中間の積はi128を使う。

関連のfztはAND/OR、fwtはXOR変換。入力長は1以上の2冪、空列・非2冪長は対象外。XORの逆変換では長さによる除算ができる係数型を使用する。テストでは法998244353のmintで往復と素朴畳み込みを検証する。
