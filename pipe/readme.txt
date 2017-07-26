計算機システム構成原理I 演習　第13回課題　15TI023 池崎雄介

[ファイルの説明]
lsgrep.c : 引数にディレクトリ名dirと文字列nameを与えると、"ls -l dir | grep name"と同じ出力をするプログラムのソースファイル
　　　　　　　コンパイル方法： gcc lsgrep.c -o lsgrep
lsgrep　 : lsgrep.c の実行形式ファイル
　　　　　　実行方法： ./lsgrep dir name
square.c : intの整数値を親プロセスから子プロセスに渡し、子プロセスでその整数値を2乗した後、親プロセスに戻すプログラムのソースファイル
　　　　　　　コンパイル方法： gcc square.c -o square
square　 : square.c の実行形式ファイル
　　　　　　実行方法： ./square  output_file
readme.txt : このファイル


[課題について]
課題２について： 作成したプログラムのソースファイル（lsgrep.c）
	         工夫した点：　lsの出力ファイルを用意し、grepでそのファイルを検索する。無駄なファイルを残さないように、最後にそのファイルを消去している。

課題３について： 作成したプログラムのソースファイル（square.c）
	         工夫した点：　〇〇〇〇〇〇〇〇
	　　　　 質問したい点：　〇〇〇〇〇〇〇〇

