---
title: 素数判定・素因数分解
documentation_of: //src/math/prime.hpp
---

is_primeは符号付きllの整数を判定する。factorは正のllを素因数列へ分解し、1なら空列。pollard_singleは2以上の整数の非自明な因子（素数なら自身）を返す。rndとi128に依存する。

pow_modは非負底・非負指数・正の法で、乗算がTに収まること。大きなll法には `pow_mod<i128>` を使う。primitive_rootは素数p>=2が前提で、p=2では1。単体テストはrnd依存を同じ分布の固定seed関数で与え、因子を独立した試し割りや既知の分解と比較する。
