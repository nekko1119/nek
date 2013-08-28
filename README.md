# nek C++ ライブラリ
ライブラリという体を取っていますが、ただのソースコードの寄せ集めです。  
自己満足、趣味、勉強用、劣化車輪の再発明です。  
主にSTLやBoostのライブラリで興味を持ったものを劣化コピーしていきます。

##現在の目標
std::vectorを再現すること  
その為にallocatorやiteratorを作っています

## 開発環境
 * OS
  - windows 7 32bit
 * コンパイラ
  - VC11.0 Nov 2012 CTP
  - VC12.0 Preview

## コンパイラのC++11/C++14対応メモ

### constexpr
未対応

### 関数のdelete/default指定
未対応

### 初期化リスト
`vector<int> v({1, 2, 3})`がコンパイルエラーになります。 
配列メンバ変数を初期化子リストで初期化できません。

    class A
    {
        int ar[3];
    public:
        A() : ar{1, 2, 3}
        {
        }
    };

### noexcept
未対応

### ユーザー定義リテラル
未対応

### ムーブコンストラクタとムーブ代入演算子の自動生成
未対応

### decltype
`decltype(expr)::type`のように、decltypeから直接、メンバ型にアクセスすることができません。

### STL  
std::forwardとstd::declvalがtype_traitsヘッダで定義されています。

### 最後に  
環境依存バリバリなソースコードです。上記の環境でしか確認していません。
