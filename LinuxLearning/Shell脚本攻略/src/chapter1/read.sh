# using 'read' command to read text from keyborad or stdin.
# read -option variable_name

# read n chars from stdin and saved in var
read -n 2 var
echo $var

# -s undisplay reading
read -s var
echo $var

# -p show message
read -p "Enter input:" var
echo $var

# -d using special char as an inputing end sign
read -d ";" var
echo $var

