# TODO

## Lexer: sueda

## Expander: sueda

## Parser: tkisaku

## Executor: tkisaku

最低限の機能: 6/1

### Bult-in: 時間余ったほう

#### echo

#### cd

#### pwd

#### export

#### unset

#### env

#### exit

### External: tkisaku

最低限の機能: 6/1

## 全体の処理

### シグナル管理: sueda

最低限の機能: 5/30

### エラー処理

### ヘッダーの整理

依存関係のことを調べてヘッダーは小分けするべきかどうかを学び実装したい。

## 時系列

### 5/27(火曜) 13:00に42Tokyoに集合

#### sueda

- [ ]lexer
- [ ]expander
  - [ ]$?
  - [ ]"", ''の展開
- [ ]暇になったら全体
  - [ ]シグナル（$?を実装できるようにグローバル変数を定義）
  - [ ]minishell絵文字を左に表示+コマンドを待ち受けてエンターでその文字列を取得

#### tkisaku

- executorのexternalをエラーハンドリングなし
