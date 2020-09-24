# "diff" is used to compare the differend between files
# option '-u' can be used to format show the differece betweem files
diff -u diff1.txt diff2.txt

# "patch" is used to modify the file that is based on the other file
# first, create a patch file
diff -u diff1.txt diff2.txt > diff.patch
# second, modify the target file
patch -p1 diff1.txt < diff.patch
# third, reverse the patch operation
patch -p1 diff1.txt < diff.patch
# the former command also can be typed as "patch -p1 -R diff1.txt < diff.patch" to undisplay the prompt info
