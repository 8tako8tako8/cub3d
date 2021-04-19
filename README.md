# cub3D

## Overview
42Tokyoの課題。
ray castingという技術を用いて3D空間を実装する。
武器や敵は未実装。
map内にある樽を見つける。

## Requirement
- mac Catalina 10.15.7
    - or
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
### map_fileについて
- R 500 400 <- ウィンドウの大きさを指定
- NO ./textures/eagle.xpm <- 北側のテクスチャを指定
- SO ./textures/greystone.xpm <- 南側のテクスチャを指定
- WE ./textures/redbrick.xpm <- 西側のテクスチャを指定
- EA ./textures/purplestone.xpm <- 東側のテクスチャを指定
- S ./textures/barrel.xpm <- スプライトのテクスチャを指定
- F 255,255,255 <-床の色をRGB(0~255)で指定
- C 30,30,255　<-天井の色をRGB(0~255)で指定

### 移動方法
(W): 前進
(S): 後退
(A): 左回転
(D): 右回転
(←): 左横移動
(→): 右横移動
(Esc): 終了

<li>樽を見つけるゲーム(樽を見つけてもゲームは終了しません。)</li>

![meiro](https://raw.github.com/wiki/8tako8tako8/cub3d/image/meiro.gif)

## About debug
略

## Reference
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [cub3D(lodev日本語訳)](https://hackmd.io/@DgDJ9MK0TVKVtdxd5qPreg/SJO5DOx2v)
