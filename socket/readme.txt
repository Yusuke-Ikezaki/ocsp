計算機システム構成原理I 演習　第14回課題　15TI023 池崎雄介

[ファイルの説明]
chat_server.c : 簡易的なチャットプログラムのサーバ側のソースファイル
　　　　　　　コンパイル方法： gcc chat_server.c -o chat_server
chat_server　 : chat_server.c の実行形式ファイル
　　　　　　実行方法： ./chat_server ポート番号
chat_client.c : 簡易的なチャットプログラムのクライアント側のソースファイル
　　　　　　　コンパイル方法： gcc chat_client.c -o chat_client
chat_client　 : chat_client.c の実行形式ファイル
　　　　　　実行方法： ./chat_client 接続ホスト ポート番号
readme.txt : このファイル


[課題について]
課題２について： 作成したプログラムのソースファイル（chat_server.c, chat_client.c）
	         工夫した点：　リスト1とリスト2のプログラムを最大限活用して、サーバ側には送信をするコードを、クライアント側には受信をするコードをそれぞれ付け足した。
