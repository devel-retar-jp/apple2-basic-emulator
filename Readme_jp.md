# Apple II Plus Emulatorについて

A minimal Apple II Plus (1979) emulator 
with auto-generated ROMs, 
demonstrating faithful 6502 CPU emulation 
and Applesoft BASIC support on vintage hardware.

------------------------------------------------------------
## 0. Apple II PlusのROM BASICの機能

### 入出力

- **入力**: BASIC コードを Windows のエディタで編集
  - テキストファイルとして編集
  - 改行 CRLF, ASCII コード
  - エミュレータの実行ファイルから引数として読み込み

- **出力**: テキスト画面（40×24）
  - Apple II Plus の標準テキストモード
  - ASCII コード 35-126（96文字制限）
  - 出力範囲外の文字は、別の文字に置き換えられます

### 動作モード

- **バッチモード**: -> 実装済み
  - BASIC プログラムをファイルから読み込んで実行
  - スクリプト的な使用法

- **対話モード (REPL)**: -> 未実装
  - キーボードからのインタラクティブ操作
  - 将来の改造ポイント（コントリビューション歓迎）

### 技術仕様

- **CPU**: MOS 6502 エミュレーション（fake6502）
- **メモリ**: 48KB RAM + 12KB ROM
- **キャラクタセット**: ASCII 35-126（96文字）
- **ROM 初期化**: 自動生成
- **乱数 SEED**: 1バイト書き込み仕様

### ライセンス

**GNU General Public License v2.0**

このプロジェクトは fake6502 (GPL 2.0) に依存しているため、GPL 2.0 でライセンスされています。

詳細は `LICENSE` ファイルを参照してください。

------------------------------------------------------------
## 1. Apple II Plus Emulatorの構築手順書

### プラットフォーム対応

- **Windows** (Visual Studio 2026): -> 開発・検証完了
- **Linux/macOS**: 軽微な修正で対応可能（コントリビューション歓迎）

### 必要な環境

- **OS**: Windows 11
- **IDE**: Visual Studio 2026 以上
- **CMake**: 3.20 以上
- **C++**: C++20 対応コンパイラ
- **vcpkg** (オプション): 依存関係管理用(奨励)

```
# ビルド
cmake CMakeLists.txt
```

------------------------------------------------------------
## 2. ソースコードのダウンロード
### GitHub から

```bash
git clone https://github.com/YOUR_USERNAME/apple2-basic-emulator.git
cd apple2-basic-emulator
```

------------------------------------------------------------
## 3. ROMのダウンロード

### ROM 生成の詳細
「Apple IIとBASICまとめ」として歴史的な経緯をまとめました。
詳細は`docs/Apple2Plus_ROM_Make_jp.md` を参照してください。

### 知的財産への対応

- Apple II ROM は Apple Computer, Inc. の保護対象です
- このエミュレータは ROM ファイルを配布しません
- ユーザーが正規 ROM から生成データを取得する構成です

------------------------------------------------------------
## 4. サンプル BASIC コードの実行

### BASICサンプルプログラム

#### codeTest.bas - 96文字セットテスト

このプログラムは Apple II Plus Monitor ROM がサポートする
96文字（ASCII 35-126）を全て表示します。

#### **実行方法**:

```
.\apple2-emulator.exe codeTest.bas
```
------------------------------------------------------------
## 5. Apple II PlusのROM BASICの簡易マニュアル

詳細は `docs/APPLE2_BASIC_REFERENCE_jp.md` を参照してください。


------------------------------------------------------------
## 6. dumpTool

バイナリファイルなどの解析のためにつくりました。
実際に開発で利用しているもの。

### 使い方
```
     dumpTool.exe -f 対象ファイル [-b|-h|-d]

     -b : ビット列  -> 対象ファイル名_BYTE.txt
     -h : 16進      -> 対象ファイル名_HEX.txt
     -d : 10進      -> 対象ファイル名_DEC.txt
     指定なし       -> 上記3種すべてを出力
```
