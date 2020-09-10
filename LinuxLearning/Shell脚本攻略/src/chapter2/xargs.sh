# xargs is used to format the data obtained from stdin and provide it as parameters to other commands.

# you can use xargs to transform multiple text lines to single or opposite usage.
cat xargs1.txt | xargs
# using the command option '-n' to determine the lines
cat xargs2.txt | xargs -n 3

# in addition to using space, option '-d char' can be used to separtate parameters by customize.
echo "arg1Xarg2Xarg3Xarg4" | xargs -d X
echo "arg1Xarg2Xarg3Xarg4" | xargs -d X -n 2

# you can use option '-n number' to set the numbers of parameter used by other commands.
cat xargs2.txt | xargs -n 1 bash xargsEcho.sh
cat xargs2.txt | xargs -n 3 bash xargsEcho.sh
# you can use option '-I {}' to specify the replacement part of a combatination command.
cat xargs2.txt | xargs -I {} bash xargsEcho.sh -p -s {} -l



