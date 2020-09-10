# cat--concatenate which is used to read, display or concatenate file contents

# you can print multiple files' content using 'cat file1.txt file2.txt ...'
cat cat1.txt cat2.txt

# concatenate the stdin and file's content by using pipe '|'
# echo string | cat - file.txt 
# using '-' to represent the filename of stdin
echo "Text through stdin" | cat - cat1.txt

# you can choose some options when using cat command like -s to clear the space between lines and -n to show line number
cat -s cat1.txt
cat -n cat2.txt
