# TODO

## Lexer: sueda

## Parser: sueda

## Expander: sueda

- シングル、ダブルクオート、環境変数、特殊変数（$?など）を展開

  #?: 必ず実装。
  以下は（あくまでも代表例だが）要検討（文末に戻り値を記載）。
  (チャッピー曰く、あくまでも指定された要件を実装すれば良いため、実装しないグループがとても多い)

  $$
  : ❌get_pid()が使用不可能のため実装不可。空文字を返す。
  $!: ▲再現可能だが""を返す。
  $0: ◯常に"minishell"を返す
  $1~$9...: ◯常に""を返す。
  $#: ◯常に０を返す。
  $*: ◯常に""を返す。
  $@: ◯常に""を返す。
  $_: ▲再現可能だが""を返す。
  $-: ▲簡易版は実装可能（相当複雑らしい）。空文字を返す。
  $$

## Validator: sueda

## Executor: tkisaku

- 文法チェックはしない（Executorには完璧なデータが渡る）

### Bult-in: 時間余ったほう

#### echo

#### cd

#### pwd

#### export

#### unset

#### env

#### exit

### External: tkisaku

## 全体の処理

### シグナル管理

### エラー処理

### ヘッダーの整理

依存関係のことを調べてヘッダーは小分けするべきかどうかを学び実装したい。

## 時系列

### 5/27(火曜) 13:00に42Tokyoに集合

#### sueda

- [x]lexer
- [ ]expander
  - [ ]$?
  - [ ]"", ''の展開
- [ ]暇になったら全体
  - [ ]シグナル（$?を実装できるようにグローバル変数を定義）
  - [ ]minishell絵文字を左に表示+コマンドを待ち受けてエンターでその文字列を取得

#### tkisaku

- executorのexternalをエラーハンドリングなし
- error処理について調べる

### 5/31(Sat) 10時にneko集合

#### sueda: 下準備のところを学ぶ

- 関数の役割をしっかりと定義する
- 展開
- 文法チェック、スペルチェック
- Executorが処理しやすいようにデータを変換
-

#### tkisaku: Executorの実装をやりゴールを作る

#### 参考記事
