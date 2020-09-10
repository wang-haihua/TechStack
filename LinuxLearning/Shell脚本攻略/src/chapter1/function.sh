# declare a function like "function fname(){}" or "fname(){}"
# execute a funciont like "fname ;" or including parameters like "fname arg1 arg2;"
#!/bin/bash
fname()
{
    echo $1, $2;
	echo "$@";
	echo "$1""$2";
	echo "$*";
	echo "$1,$2";
}
fname 1 2;
