# command "comm" is used to obtain different files' intersection, substraction and difference.

# First of all, the files content should be sorted
sort comm1.txt -o comm1.txt; sort comm2.txt -o comm2.txt

echo "first second third"
# 
comm comm1.txt comm2.txt

# obtain intersection
echo "intersection"
comm comm1.txt comm2.txt -1 -2

# obtain set difference
echo "A set difference"
comm comm1.txt comm2.txt -2 -3

echo "B set difference"
comm comm1.txt comm2.txt -1 -3
