#!/bin/bash
REPO_URL="git@vogsphere-v2.42tokyo.jp:vogsphere/intra-uuid-dd82e4af-0d4e-4c9e-85d9-238f0d1b936d-6669984-tkisaku"
HASH_FILE="git-hash.txt"
git rev-parse --short HEAD >$HASH_FILE
WORK_DIR="../minishell-$(cat $HASH_FILE)"

git clone "$REPO_URL" "$WORK_DIR"
rsync -a --exclude='.git' . "$WORK_DIR"
cd "$WORK_DIR" || exit
cp .gitignore .gitignore.tmp
cat .gitignore.tmp .vogsphereignore >.gitignore
rm .gitignore.tmp

git add .
git commit -m "$(cat $HASH_FILE)"
git push
