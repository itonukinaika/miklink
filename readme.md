#miklink v0.1 by 糸貫内科クリニック
コニカミノルタのREGIUS UNITEAと電子カルテを連携させる際、標準の連携プログラム「kimlink」の起動に大変時間がかかるため、同機能を再実装したもの。


このプログラムは実証試験であり、バッファーオーバーフローの対策は全く行っていない。実用するには修正が必要。

##使い方：
電子カルテ等からUNITEAの画面を開くには、
miklink.exe UNITEAサーバのIP UNITEAサーバのポート UNITEAサーバのユーザ名 患者番号 open

###NTT東日本 FC21Warpでの設定例：
「汎用ローカルアプリ」「実行プログラムの引数」に、 XX.XX.XX.XX 80 KM-USR-00001 [@sinsatuken_no] open

