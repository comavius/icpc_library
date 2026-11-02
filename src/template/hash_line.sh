# 使い方: sh hash_line.sh < main.cpp (または標準入力にコピペして Ctrl + D)
code=""
g++ -dD -E -P -fpreprocessed - | while IFS= read -r line; do
   code=$code$line
   hash=$(printf '%s' "$code" | tr -d '[:space:]' | md5sum | cut -c-2)
   printf '%s  %s\n' "$hash" "$line"
done
