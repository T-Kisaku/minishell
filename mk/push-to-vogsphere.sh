#!/bin/bash
REPO_URL="git@vogsphere-v2.42tokyo.jp:vogsphere/intra-uuid-384626b4-8483-4b76-9918-988b7b2fdb59-6579262-tkisaku"
HASH_FILE="git-hash.txt"
git rev-parse --short HEAD >$HASH_FILE
WORK_DIR="../minishell-$(cat $HASH_FILE)"
# TMP_DIR="../minishell-tmp-$(cat $HASH_FILE)"

git clone "$REPO_URL" "$WORK_DIR"
rsync -a --exclude='.git' . "$WORK_DIR"
cd "$WORK_DIR" || exit
cp .gitignore .gitignore.tmp
cat .gitignore.tmp .vogsphereignore >.gitignore
rm .gitignore.tmp

git add .
git commit -m "$(cat $HASH_FILE)"
git push
