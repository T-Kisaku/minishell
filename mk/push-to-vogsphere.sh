#!/bin/bash
REPO_URL="git@vogsphere-v2.42tokyo.jp:vogsphere/intra-uuid-384626b4-8483-4b76-9918-988b7b2fdb59-6579262-tkisaku"
HASH_FILE="git-hash.txt"
WORK_DIR="../minishell-$(cat $HASH_FILE)"

cp -r . "$WORK_DIR"
cd "$WORK_DIR" || exit
git rev-parse --short HEAD >$HASH_FILE
cp .gitignore .gitignore.tmp
cat .gitignore.tmp .vogsphereignore >.gitignore
rm .gitignore.tmp

rm -rf .git

git init
git remote add origin $REPO_URL
git add .
git commit -m "$(cat $HASH_FILE)"
git branch -M master
git push -f origin master
