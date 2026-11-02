---
title: FFT (高速フーリエ変換 / 畳み込み)
documentation_of: //src/FPS/FFT.hpp
---
- 参考実装：[gifted infants](https://yosupo.hatenablog.com/entry/2019/07/02/122433)

## Depends on

- [Modint](../modint/modint.hpp)

## 使い方

- `void fft(vector<mint>& a, bool inv = false)`：長さが $n$ : $2$ べきの数列 $a$ の離散フーリエ変換を行う．`inv = true` で逆変換を行う．
    - $f(x) := a[0] + a[1]x + \dots + a[n - 1]x^{n - 1},\ \omega := e^{i\frac{\tau}{n}}$ としたとき，列 $[f(\omega^0), f(\omega^1), \dots, f(\omega^{n-1})]$ を返す．
    - **bit reversal 順ではないことに注意**
- `vector<mint> mul(vector<mint> a, vector<mint> b)`：数列 $a, b$ の畳み込みを行う．一方が空なら空列を返す．
    - $c[k] := \sum_{i + j = k}a[i] \times b[j]$ で定義される，長さ $\text{sz}(a) + \text{sz}(b) - 1$ の数列 $c$ を返す．

$O(n \log n)$ 時間

## 注意

- 法は $998244353$、原始根は $3$．`fft()` の入力長は $1$ 以上 $2^{23}$ 以下の 2 べきであること．畳み込みで FFT を使う場合も、ゼロ詰め後の長さがこの範囲に収まること．
- **IFFT は，FFT における $[\omega^1, \dots, \omega^{n-1}]$ を $[\omega^{n-1}, \dots, \omega^{1}]$ で置き換えたものなので，FFT の結果の $[f(\omega^1), \dots, f(\omega^{n-1})]$ の部分を reverse すれば良い．出力を reverse する代わりに，入力の同じ部分を reverse しても良い．**
- FFT → IFFT をすると各要素が $n$ 倍されるので、$n$ で割る必要がある
