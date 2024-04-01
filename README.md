# TamakoroGame（玉転がし）

[![Release](https://github.com/FugoShimizu/TamakoroGame/actions/workflows/release.yml/badge.svg)](https://github.com/FugoShimizu/TamakoroGame/actions/workflows/release.yml)

ＤＸライブラリ製の３Ｄ玉転がしミニゲームです．自動生成された迷路状のステージ（盤）を傾け，転がる玉をスタートからゴールへ導きます．

![TamakoroGame](graphs/title.png)

## 特徴
- **自動生成迷路** … 四角形／六角形の２形状．サイズ・シードを指定出来，同じシードなら同じ迷路を再現します．
- **直感的な操作** … マウス左ドラッグ又は WASD でステージ其の物を傾けて玉を転がします．
- **３Ｄ表現** … シャドウマップ（近景・遠景の２枚）とディレクショナルライトに依る陰影付の３Ｄ描画．
- **ミニマップ** … 右下に全体図を表示（ズーム対応）．
- **タイム計測** … クリアタイムを計測し，ゴール後には解いた経路（軌跡）をアニメーション表示．
- **リトライ／タイトル復帰** … 同設定での再挑戦やタイトルへの復帰が可能．
- **単一exe で配布** … アセットを暗号化して exe に埋め込み，ランタイムも静的リンク．`TamakoroGame.exe` だけで追加インストール不要・どこでも動作．

## 動作環境
- **OS**: Windows 10 / 11
- **描画**: DirectX（ＤＸライブラリ Ver 3.24 系）
- **解像度**: 1280×720 ウィンドウモード（4x アンチエイリアス）

## 遊び方（起動）
アセット（モデル・画像・音）は**暗号化アーカイブとして exe に埋め込まれている**為，**`TamakoroGame.exe` 単体でどこでも動作**します（別ファイル・インストール・カレントディレクトリ設定は一切不要）．

- **配布版で遊ぶ**: [Releases](https://github.com/FugoShimizu/TamakoroGame/releases) から `TamakoroGame-x64.exe`（64bit）又は `TamakoroGame-x86.exe`（32bit）をダウンロードし，ダブルクリックするだけです．
- **Visual Studio**: `TamakoroGame.sln` を開いて **F5**．

起動後，タイトル画面の「プレイ」（又は Enter）でゲーム開始です．

## 設定（タイトル画面）
| 項目 | 内容 |
|---|---|
| ステージの形 | 四角形／六角形／ランダム |
| ステージの大きさ | 2~32 のスライダー／ランダム（既定 16）|
| ステージのシード | 任意の整数／ランダム（同じ値で同じ迷路を再現）|

## 操作方法
### プレイ中
| 操作 | 内容 |
|---|---|
| マウス左ドラッグ／W・S・A・D | ステージを前後左右に傾ける |
| 矢印キー | 視点を上下左右に移動する |
| R | 視点を初期位置に戻す |
| F5 | 視点を切り替える |
| U | 玉をスタート位置に戻す |
| M | ミニマップの表示／非表示を切り替える |
| マウスホイール | 視点を拡大・縮小（カーソルがミニマップ内なら，ミニマップを拡大・縮小）|
| F3 | デバッグ表示の表示／非表示を切り替える |
| T | タイトルに戻る |

### ゴール後
| 操作 | 内容 |
|---|---|
| 軌跡確認 | 玉が通った解法経路をアニメーション表示 |
| 再プレイ／Enter | 同じ設定で再挑戦する |
| タイトル | タイトル画面に戻る |

## ビルド方法
### 必要な物
- **Visual Studio 2022**（プラットフォームツールセット v143／C++20／文字セット：マルチバイト）
- **ＤＸライブラリ VC++ 用パッケージ**（Ver 3.24 系）… <https://dxlib.xsrv.jp/>

### ローカルビルド
本プロジェクトはＤＸライブラリの参照先を `$(DxLibDir)` プロパティで指定しています．既定値は次のパスです（ＤＸライブラリの「プロジェクトに追加すべきファイル_VC用」フォルダ）．

```
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.31.31103\include\dxlib
```

別の場所に配置している場合は，上書きしてビルド出来ます．

```bash
msbuild TamakoroGame.sln /p:Configuration=Release /p:Platform=x64 /p:DxLibDir="C:\path\to\dxlib"
```

Visual Studio で開いてビルドする場合は，上記の既定パスにＤＸライブラリを配置するか，プロジェクトの `DxLibDir` を環境に合わせて変更してください．

アセットは `models.dxa`・`graphs.dxa`・`sounds.dxa`（暗号化アーカイブ）として [`resource.rc`](resource.rc) 経由で exe に埋め込まれます．`models/`・`graphs/`・`sounds/` を変更した際は，ＤＸライブラリ付属の DxaEncode で対応する `.dxa` を再生成してください（鍵は `source/main.cpp` の `SetDXArchiveKeyString` と一致させる）．

## プロジェクト構成
```
TamakoroGame/
├─ source/                          … C++ ソース（ゲーム本体）
├─ models/ graphs/ sounds/          … アセットのソース（.mv1・.png・.mp3）
├─ models.dxa graphs.dxa sounds.dxa … 暗号化アセットアーカイブ（exe へ埋込）
├─ resource.rc                      … アーカイブを exe に埋め込むリソース定義
├─ .github/workflows/release.yml    … GitHub Actions（v* タグ push でビルド＆リリース）
├─ TamakoroGame.sln / .vcxproj      … Visual Studio プロジェクト
└─ README.md
```

主なモジュール（`source/`）:
- **main** … エントリポイント・メインループ・アーカイブ登録
- **title_screen／play_screen／loading_screen** … 各画面
- **setting** … ステージ設定（形・サイズ・シード）
- **maze_sqr／maze_hex** … 迷路生成（四角形／六角形）
- **stage_sqr／stage_hex・cell_\*・block_\*** … ステージ・セル・ブロックの構築
- **model** … ３Ｄモデル管理・玉の物理シミュレーション・描画
- **ball／camera／button／input／time** … 玉・カメラ・UI・入力・時間管理

## 技術的な特徴
- シード付擬似乱数（`std::mt19937`）に依る**決定論的な迷路生成**
- 四角形セル／三角形セルに依る**２種類の迷路形状**
- シャドウマップ２枚（近景 4096² ＋ 遠景 4096²）に依る影の描画
- 玉とブロックの衝突判定（距離・角度ベース）
- ミニマップ・解法軌跡の表示
- 暗号化ＤＸアーカイブをリソースとして exe に埋め込み，メモリから読込（単一exe 配布）

## クレジット
- ゲームライブラリ: [ＤＸライブラリ](https://dxlib.xsrv.jp/)（Ver 3.24 系）
