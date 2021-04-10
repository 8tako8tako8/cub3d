# cub3D

## Overview
42Tokyoの課題。
ray castingという技術を用いて3D空間を実装する。
武器や敵は未実装。
map内にある樽を見つける。

## Requirement
- mac Catalina 10.15.7
or
- XUbuntu 18.04.5

## Usage
```
git clone ...
cd cub3d
make re
./cub3D map_file/meiro.cub
```
スタートポジションのbmp作成
```
./cub3D map_file/meiro.cub --save
```
移動方法
(W): 前進
(S): 後退
(A): 左回転
(D): 右回転
(←): 左横移動
(→): 右横移動
(Esc): 終了

<li>樽を見つけるゲーム(樽を見つけてもゲームは終了しません。)</li>
![meiro](/image/meiro.gif)

## About debug
略

## Reference
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [cub3D(lodev日本語訳)](https://hackmd.io/@DgDJ9MK0TVKVtdxd5qPreg/SJO5DOx2v)

## Author
[twitter](https://twitter.com/totti13101176)
