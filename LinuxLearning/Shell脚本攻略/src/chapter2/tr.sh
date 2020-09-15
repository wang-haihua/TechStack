# command 'tr' is used to translate char, delete char or zip char from stdin. It's format like ' tr [options] set1 set2 '. set1/set2 always content many chars reperented by '起始字符-终止字符'

# translate char
echo "HELLO WHO IS THIS" | tr 'A-Z' 'a-z'
echo 12345 | tr '0-9' '987654321'
echo 87654 | tr '987654321' '0-9'

# delete char 'cat file.txt | tr -d set1
echo "Hello 1234 World 35632" | tr -d '0-9'

# char class such as alnum, alpha, cntrl and so on...
