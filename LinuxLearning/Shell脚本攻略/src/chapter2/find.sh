# find命令用于搜索文件，沿着文件层次结构向下遍历，匹配符合条件的文件，执行相应的操作。
# show all directories and files by using "find base_path"
# -print means printing the path of files
find . -print 

# 1. using Regular Expression or filename to search file
# find base_path -name "RegularExpressiong" -print
find . -name "*.txt" -print
find . -name "cat.sh" -print
# you also can use "-iname" to ignore the Case difference like(CAT/cat)
# using mulitple filter condition to search files like "\( -name '*.txt' -o -name '*.sh' \)"
# find . \( -name "*.txt" -o -name "*.sh" \) -print

# 2. ! negation sign to search the reverse range
find . ! -name "*.txt" -print

# 3. setting the searching depth by using "-maxdepth/-mindepth"
find . -maxdepth 1 -name "f*" -print

# 4. searching files by their types like "f, l, d, c ..."
find . -type f -print

# 5. searching files by access time, modify time and change time
# -atime -mtime -ctime   using "+/-" represent greater or less
find . -type f -atime -7 -print

# 5. searching files by the size of files
find . -type f -size -1k
