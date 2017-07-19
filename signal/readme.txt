計算機システム構成原理Ⅰ 第12回課題 15TI023 池崎雄介

ファイルについて
finger.c	:fingerコマンドを何度も実行できるプログラム
			gcc finger.c -o finger
finger		:finger.cの実行形式ファイル
			./finger
stop_watch.c	:ストップウォッチプログラム
			gcc stop_watch.c -o stop_watch
stop_watch	:stop_watch.cの実行形式ファイル
			./stop_watch
readme.txt	:このファイル

課題について
課題2		:ソースファイル(finger.c)
		 アカウント名を入力したときは「finger <入力した文字列>」を実行し、改行のみを入力したときは引数なしのfingerを実行する。exitを入力すると終了する。
課題3		:ソースファイル(stop_watch.c)
		 プログラムを実行すると計測が始まり、Ctrl-cを押すと一時停止して、経過時間を表示する。そこからrを入力するとリスタートし、qを入力すると合計計測時間を表示して終了する。
