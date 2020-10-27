# usage: calculate the cpu usage of processes in an hour

SECS=360 # the total watching time
UNIT_TIME=60 # the Stride

STEPS=$(( $SECS / $UNIT_TIME))

echo Watching CPU usage ...;

for((i=0;i<STEPS;i++))
do
	# 'ps -eo comm,pcpu' is used to output all processes' names and its CPU usage in percent. 'comm' means command name and 'pcpu' means CPU usage in percent.
	# 'tail -n +2' is used to extract COMMAND %CPU from the output of command 'ps'
	# 'cpu.usage.$$' is used to save the information and '$$' means the PID of current process
    ps -eo comm,pcpu | tail -n +2 >> cpu.usage.$$
    sleep $UNIT_TIME
done

echo
echo CPU eaters :

# calculate the CPU usage and display it
cat cpu_usage.$$ | \
awk '
{ process[$1]+=$2;}
END{
  for(i in process)
  {
    printf("%-20s %s\n",i, process[i]);
  }
}' | sort -nrk 2 | head

