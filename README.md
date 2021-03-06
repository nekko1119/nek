[![Build Status](https://travis-ci.org/nekko1119/nek.svg?branch=develop)](https://travis-ci.org/nekko1119/nek) [![Coverage Status](https://coveralls.io/repos/nekko1119/nek/badge.png?branch=develop)](https://coveralls.io/r/nekko1119/nek?branch=develop) [![Build status](https://ci.appveyor.com/api/projects/status/vwppraps0fvu3ikl?svg=true)](https://ci.appveyor.com/project/nekko1119/nek)

# C++ 写経コード
このコード群の目的は2つあります。

* 自分の勉強用
* 他人の勉強用

　1つめは自分のC++の勉強の手段として、STLやBoostの写経をすることです。実装を通して様々なテクニックやイディオムを身につけることが目的であり、使用することが目的ではありません。(使用するのが目的ならば再発明せずオリジナルのライブラリを使います。)

　2つめは他のC++学習者のサンプルコードにすることです。勉強目的でBoostやSTLを読むということはあると思います。ですが使われているテクニックやイディオムを処理を理解する前に、プリプロセスの解読やワークアラウンドの解読で力尽きてしまう人も結構いるのではないかと思います。そこで、あえてポータビリティなどを犠牲にし、簡潔したコードでBoostやSTLを写経しようと思いました。
　理想は全体がサンプルコードの集合のようになることです。

 と、色々御託を並べていますが、本当のところは車輪の再発明は楽しいのでやっているところも大きいです。

## 現在の目標
std::vectorを再現すること
その為にallocatorやiteratorを作っています。
それに使うユーティリティやtype_traitsなどを書いています。
注意として、標準にあるクラスと同等の機能を持ったクラスを作ることが目標で、
完全にインターフェイスを同じにするつもりはありません。なるべく非static非メンバ関数、非フレンド関数にしようとしますし、`empty() const`ではなく`is_empty() const`と名前をつけたりします。

anyはなんとなく書きました……　面白かったです。

## 最終目標
C++標準ライブラリ(STL含む、言語サポートライブラリとIOと排他制御とスレッド関連除く)と、Boostの中からいくつかを再現実装できたら良いなと思っています。

### とりあえず第１段階として実現したいなあと思っているもの

 - [ ] `<algorithm>`より、vectorの実装に使うもの
 - [ ] `std::vector`
 - [ ] `iterator_traits`、`next`、`prev`、`advance`、`distance`周り　
 - [x] `std::allcator`、`std::allcator_traits`、`std::pointer_traits`、`std::addressof`
 - [x] `boost::any`
 - [x] `boost::noncopyable`
 - [x] `<utility>`より、`move`、`move_if_noexcept`, `forward`、`swap`、`declval`
 - [ ] `boost::mpl`から簡単なもの(`integral_c`、`bool_`、`if_`、`eval_if`、`identity`)と上記実装に使いそうなもの
 - [ ] `<type_traits>`より、上記の実装に必要なもの
 - [ ] その他、標準、boostには無いが作ってみたもの

### 作らないもの

 - 各iostream　(ios、ios_base、sstream、fstreamなど)
 - atomic、mutex、thread、futureなど
 - exception、stdexceptなど
 - initializer_list
 - cstdint、climit、limits、cstdio、cstdlib、cstddefなど
 - locale、codecvtなど

## 開発環境
 * OS
  - windows 10 64bit
  - Ubuntu 14.04
 * コンパイラ
  - VC14.1 RTM
  - gcc 4.9.2

## 最後に
環境依存バリバリなソースコードです。上記の環境でしか確認していませんし、上記の環境ででしか動かないと思いますし、上記以外をサポートする予定はありません。
