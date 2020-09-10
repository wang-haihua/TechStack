# each command called filter is connected by pipe one by one, such as "cmd1 | cmd2 | cmd3". The output of the previous command is used as the input ofthe subsequent command.

#!/bin/bash
ls | cat -n > out.txt

# two types of the subshell
cmd_output1=$(ls | cat -n)
echo $cmd_output1

cmd_output2=`ls | cat -n`
echo $cmd_output2

