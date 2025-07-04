# Review by haito

## コメント

お疲れ様でした！頑張りましょう！！

- readlineに空白だけ入った場合クラッシュ
- catなどブロッキングコマンドでCtrl+Cを入力したときプロンプトが二回表示される
- 同じくCtrl+\はbash like にする
- minishellの中でminishellを起動したときのシグナル処理
- exportだとvalueがNULLでも表示される
- unset PATH されたときカレントディレクトリを参照する
- unset HOME のあとhome以外のディレクトリからhomeにcdするときメモリリークとエラー違い
- ヒアドク中のCtrl+C
- エラーメッセージが標準出力になっている
- ブロッキング関数実行中に改行しても^Mになってしまう。execveするときリダイレクトが標準入力からじゃなくなっている可能性あり
- echo "'$USER'"は展開されるべき

## TODOリスト

- [x] readlineに空白だけ入った場合クラッシュ
- [s] catなどブロッキングコマンドでCtrl+Cを入力したときプロンプトが二回表示される
- [ ] 同じくCtrl+\はbash like にする: TODO: なんかできなくなった
- [s] minishellの中でminishell
- [x] exportだとvalueがNULLでも表示される
- [x] unset PATH されたときカレントディレクトリを参照する
- [x] unset HOME のあとhome以外のディレクトリからhomeにcdするときメモリリークとエラー違い
- [x] ヒアドク中のCtrl+C
- [x] エラーメッセージが標準出力になっている
- [x] ブロッキング関数実行中に改行しても^Mになってしまう。execveするときリダイレクトが標準入力からじゃなくなっている可能性あり
