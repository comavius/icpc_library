---
title: 線形漸化式と有理母関数
documentation_of: //src/FPS/linear-recurrence.hpp
---

`LinearRecurrence(k,q,p)` はp/qのx^k係数。kは非負、qの定数項は非零。`kitamasa(k,q,a)` は初期値aと漸化式a*q=0から項を求める。初期値は次数分以上渡す。mint・FFT・fpsに依存する。
