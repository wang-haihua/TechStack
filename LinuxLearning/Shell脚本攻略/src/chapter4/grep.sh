# "grep" is used to serach the match data from massive data
# as a text seraching tool, "grep" can generate various outputs based on Regular Expression

# seraching the text lines including specific format, like 'grep pattern filename'
grep four grep1.txt

# you can seraching the specific lines from stding too
echo -e "this is the specific line\n the second line\nthe third line" | grep specific

# searching the specific lines  from multiple files, like 'grep match_text file1 file2 file3 ...'
grep four grep1.txt grep2.txt grep3.txt

# you can use option '-E' which means 'extended' to apply Regular Expression with command 'grep'
grep -E "[f]+" grep1.txt
# you also can use command 'egrep' instead of 'grep' to apply Regular Expression to search the specific lines
egrep "[o]+" grep1.txt

# option '-o' is used to print the match text only
echo "this is the specific line." | egrep -o "[a-z]+\."

# option '-c' is used to count the numbers of the matched lines
grep -c "from" grep1.txt

# option '-n' is used to display the line number of the matched lines
grep -n "three" grep1.txt grep2.txt grep3.txt

# option '-l' is used to serach the files including the match text, and option '-L' realizes the opposite funciton
grep -l grep1 grep1.txt grep2.txt grep3.txt

# one of the powerful functions of command 'grep' is that you can use it to serach match text in a directory recursively
# this command 'grep "match_text" . -R -n' is widely used by developer to serach the location of some specific texts
grep -R -n "grep1" ..

# option '-i' is used to ignore the case of match text
echo hello world | grep -i "HELLO"

# you also can match multiple patterns in one command
echo this is a line of text\nthis is the second line\n this is null | grep -e "a" -e "second"

# '--include / --exclude' is used to include or exclude some files when seraching the directory recursively
grep -r -n grep1 . --exclude *.{sh,md}

# option '-A / -B / -C + number' is used to print the match lines' prior/after/both numbers lines
grep three grep1.txt -A 3
grep three grep1.txt -B 2
grep three grep1.txt -C 2
