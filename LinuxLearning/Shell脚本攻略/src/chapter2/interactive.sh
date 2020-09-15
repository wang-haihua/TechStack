# you can design interactive input to execute shell command
read -p "Enter number:" no ;
read -p "Enter name:" name
echo You have entered $no, $name;

# input command `echo -e "1\nhello\n" | bash interactivate.sh` to execute the interactive input script in the terminal

# using redirected operator '>' to save the input date with a file, and using '<' to pop the input data to 'interactivate.sh' from input.data
# echo -e "1\nhello\n" > input.data
# cat input.data
# ./interactivate.sh < input.data
