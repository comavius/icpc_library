---
title: 中国剰余定理
documentation_of: //src/math/crt.hpp
---

`crt(b,c)` は各法cに対する剰余bから最小非負解と法の最小公倍数を返す。矛盾は `(0,-1)`、空条件は `(0,1)`。法は正、剰余は負でもよい。法の最小公倍数はllに収まること。extgcdに依存する。

関連テストではextgcdの非負入力、互いに素な正の法に対するinv_mod、binomの `0<=n<N`・範囲外m、lagrange_polynomialの非空標本・非負評価点も検証する。逆元がない入力はinv_modの対象外。補間には次数以上のifactを先にpreする。
