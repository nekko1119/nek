#nek C++ ライブラリ
ライブラリと言うのもおこがましいくらいただのソースコードの断片集です。  
自己満足、趣味、勉強用、劣化車輪の再発明。

#開発環境
 * OS windows 7
 * コンパイラ VC11.0 Nov 2012 CTP

#コンパイラの未対応
 * decltype  
`decltype(expr)::type`のように、decltypeから直接メンバにアクセスすることができません。

 * Variadic Templates
```cpp
namespace ns
{
	struct hoge {};
}

template <class... Args>
void f(Args... args)
{
}

int main()
{
	//f(hoge());//ERROR
}
```
のように、可変長テンプレート関数と異なる名前空間の型を使用すると、曽於の方は宣言されていないというエラーになる。

 * STL
なぜか、std::forwardとstd::declvalがtype_traitsヘッダで定義されている。

 * 最後に
環境依存バリバリなソースコードです。上記の環境でしか確認していません。