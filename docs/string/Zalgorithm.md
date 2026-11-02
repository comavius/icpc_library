---
title: Z Algorithm
documentation_of: //src/string/Zalgorithm.hpp
---
- 参考実装：[KACTL](https://github.com/kth-competitive-programming/kactl/blob/c52bac765cdd9cda1def052c698ffa7bd3318d29/content/strings/KMP.h)

## 使い方

- `template<typename T> vector<int> z_algorithm(const vector<T>& s)`：$Z[i] := \text{LCP}(s, s[i:])$ で定義される配列 $Z$ を求める。非空なら $Z[0]=n$、空列なら空配列。要素は等値比較できること。文字列は `vector<char>` に変換して渡す。
    - $O(n)$ 時間

## 使い方 (応用編)

- 非空のパターン $t$ の出現位置：両列に含まれない区切りを使って $t+\# +s$ のZ列を求め、後ろ $|s|$ 個から $|t|$ 以上の位置を調べる。
- 非空列 $s$ の最小周期：$s$ のZ列で、$i+Z[i]=n$ を満たす最小の $1\le i<n$。なければ $n$。

