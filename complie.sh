#!/bin/sh

# ログ消去
clear
echo "gcc complie..."
echo "\n"

# 出力するファイル名
output="Game"
# コンパイルするソース一覧
array=`find . -name "*.c"`
echo "complie targets: "
for c in $array;
do
    echo $c
done
echo "\n"

# gccコマンドでコンパイル
gcc $array -o $output
echo "Generated "$output>&1