# command "df" and "du" are used to statistics disk usage, 'df' is short for Disk Free and 'du' is short for Disk Usage

# 'du filename1 filename2 ...' is used to compute the disk usage of the files
du disk.sh

# option '-s' means summarize that can suammarize the disk usage of a couple of files
du -s ../

# option '-h' is used to show the dimension
du -h disk.sh
du -sh ../

# the couple of options such as '-b -k -m -B' are used to output result by specific unit
du -b ../
du -k ../
du -m ../

# 'df' is used to display the available space of the total disk
df -h
