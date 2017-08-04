計算機システム構成原理I 演習　第15回課題　15TI023 池崎雄介

[ファイルの説明]
mutex_count.c : int型の大域変数countを3つのスレッドで協力して30まで1ずつ加算するプログラムのソースファイル
　　　　　　　コンパイル方法： gcc mutex_count.c -o mutex_count -lpthread
mutex_count　 : mutex_count.c の実行形式ファイル
　　　　　　実行方法： ./mutex_count
readme.txt : このファイル

[課題について]
課題３について： 作成したプログラムのソースファイル（mutex_count.c）
	         工夫した点：　授業中に先生が書いたプログラムのスレッドを一つ増やした。
