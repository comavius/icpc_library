---
title: Rolling Hash
documentation_of: //src/string/RollingHash.hpp
---
- 参考実装：[tatyam](https://github.com/tatyam-prime/kyopro_library/blob/master/RollingHash.cpp)

## 使い方

- `RH rh(string s)`：文字列 $s$ に対する Rolling Hash を準備する
    - $O(n)$ 時間
- `ll rh.get(ll l, ll r)`：$s[l:r]$ の hash を求める。$0\le l\le r\le n$。空区間は $0$。
    - mod は $P := 2^{61}-1$、実装の基数は固定値 `7954398468495`。
    - このとき，長さ $n$ の文字列 $s$ の hash は $(s[0] r^{n-1} + s[1] r^{n-2} + \dots + s[n-1] r^0) \bmod P$ で計算される
    - $O(1)$ 時間
- `int rh.lcp(int i, int j)`：位置 $i,j$ から始まるsuffixのLCP長。$0\le i,j\le n$。末尾位置も指定できる。$O(\log n)$ 時間。

空文字列も構築できる。文字コードは $0$〜$127$ の範囲を使う（埋め込みNULを含む）。負の `char` 値を含む入力は検証対象外。

## 使い方 (応用編)

- LCP (Longest Common Prefix) を求めたいとき：LCP の長さを二分探索すれば，$O(\log n)$ 時間 / query
- 文字列を辞書順で比較したいとき：LCP の長さを二分探索すれば，$O(\log n)$ 時間 / query

## 衝突確率

以下は基数を一様ランダムに選ぶ場合の評価。現行実装は固定基数なので、この確率評価をそのまま保証とはできない。ハッシュ一致は文字列の厳密な等値保証ではなく、LCPにも衝突の影響があり得る。

- $2$ つの異なる長さ $n$ 以下の文字列が衝突する確率は $\frac{n}{P}$ 以下
    - 参考資料：[Schwartz–Zippel lemma による hash の解析 – noshi91](https://github.com/noshi91/blog/blob/master/pages/hash.pdf)
- 相異なる $n$ 文字の文字列 $m$ 個がどこかで衝突する確率は，$\frac{n \cdot \binom{m}{2}}{P}$ 以下
    - $(n, m) = (1, 10^6)$ を $100$ ケースやっても $0.002\%$ なので，衝突は基本的に無視できる
