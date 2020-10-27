# 'time' can be used to calculate running time of the process
time bash disk.sh

# there are three types of time
# 1. Real which means 'walk clock time', the time from start to end of the command running including the waiting time of the process
# 2. User which means the time of CPU running in User mode, only calculate the time cost by the command running process.
# 3. Sys which means the time of CPU running in System mode, calculate the time of system call
