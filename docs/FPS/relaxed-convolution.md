---
title: オンライン畳み込み
documentation_of: //src/FPS/relaxed-convolution.hpp
---

`relaxed_multiplication::add(f_i,g_i)` は順に係数を追加し、現在の積のi次係数を返す。法998244353のmintとfftに依存する。fftの逆変換は非正規化なので、結果利用時に長さの逆元を掛ける。必要なFFT長が2^23以下の範囲で使用する。
