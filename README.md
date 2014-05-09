# nek C++ ライブラリ
このライブラリの目的は2つあります。

* 自分の勉強用
* 他人の勉強用

 1つめは自分のC++の勉強の手段として、STLやBoostの車輪の再発明をすることです。実装を通して様々なテクニックやイディオムを身につけることが目的であり、使用することが目的ではありません。(使用するのが目的ならば再発明せずオリジナルのライブラリを使います。)  
  
　2つめは他のC++学習者のサンプルコードにすることです。勉強目的でBoostやSTLを読むということはあると思います。ですが使われているテクニックやイディオムを処理を理解する前に、プリプロセスの解読やワークアラウンドの解読で力尽きてしまう人も結構いるのではないかと思います。そこで、あえてポータビリティなどを犠牲にし、簡潔したコードでBoostやSTLを真似したライブラリを作成しようと思いました。  
　理想はライブラリ全体がサンプルコードの集合になることです。

## 現在の目標
std::vectorを再現すること  
その為にallocatorやiteratorを作っています

## 最終目標
C++標準ライブラリ(STL含む、言語サポートライブラリとIOと排他制御、スレッド関連除く)と、Boostの中からいくつかを再現実装できたら良いなと思っています。

## 開発環境
 * OS
  - windows 8 64bit
 * コンパイラ
  - VC12.0 CTP

### 最後に  
環境依存バリバリなソースコードです。上記の環境でしか確認していませんし、上記の環境ででしか動かないと思いますし、上記以外をサポートする予定はありません。