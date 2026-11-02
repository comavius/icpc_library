---
title: 行列と連立方程式
documentation_of: //src/math/matrix.hpp
---

`M<T>` はn行m列の行列。積の内側の次元は一致し、累乗は正方行列・非負整数指数とする。行列式は正方行列で使用する。

GaussEliminationとLinearEquationの係数型は、正規化した整数値xを持ち、非零元のinv・四則演算ができる有限体（mint等）を前提とする。実数のepsilon判定を追加する汎用solverにはしない。LinearEquationは特解と零空間の基底を返し、解なしは空結果。

主検証はLibrary Checkerのmatrix_product・matrix_det・matrix_rank・pow_of_matrix・system_of_linear_equations。補完は公式の法と異なる小体、整数係数の行列演算、公式に含まれない空次元の直接APIに限る。
