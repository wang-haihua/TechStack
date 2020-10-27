# using 'ping' to query a couple of IP address

for ip in 10.12.137.{1..255}; # {1..255} is a format of set in shell like '{start..end}'
do
	ping $ip -c 2 &> null; # '-c 2' to limit the number of eho sent by ping

	if [ $? -eq 0 ]; # '$?' is used to get the exit status, the status will be equal to 0 if it exited successfully
	then
		echo $ip is alive
	fi
done

# you also can use 'fping' to achieve the same effect
# fping -a 10.12.137/24 -g 2> null
# or
# fping -a 10.12.137.1 10.12.137.255 -g
