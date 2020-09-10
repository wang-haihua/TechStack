#!/bin/bash
# 在printf/echo命令中的双引号中引用变量值 
fruit=apple
count=5
echo "We have $count ${fruit}(s)"

# get the length of a string
length=${#fruit}
echo "the length of 'fruit' is $length"
