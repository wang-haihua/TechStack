# you can use command 'rename' to rename files in batch
count=1;
# for file in `find . -iname '*.md' -type f -maxdepth 1`
for file in `find . -iname '*.md'`
do
	new=mdfile-$count.${file##*.}
	echo "Rename $file to $new"
	mv "$file" "$new"
	let count++

done

# you can change filename's case by using "rename 'y/A-Z/a-z/' or 'y/a-z/A-Z/ *"
rename 'y/a-z/A-Z' *.md

# you can change files' suffix in batch by using 'rename'
rename *.md *.txt

# you can move the file to target directory by using ' mv {} target_dir \;
# find . -type f -name "*.md" -exec mv {} target_dir \;

