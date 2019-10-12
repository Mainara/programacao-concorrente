#!/bin/bash

if [ ! -d "bin" ]; then
	mkdir bin;
fi

if [ ! -d "results" ]; then
	mkdir results;
fi

gcc -pthread -o bin/exp exp.c --no-warnings;
gcc exp2.c -o bin/exp2 --no-warnings;

echo "structure,time,sample" > results/result.csv;
echo "structure,usage,sample" > results/result_men.csv;

function getMemoryUsage() {
	i=0
	while [ $i -lt 10 ] ; do
		sleep 0.1;
		sum=$(ps av | grep "./bin/$1" | awk '{sum+=$8}END{print sum}');
		echo "$2,$sum,$3" >> results/result_men.csv
		i=$(($i + 1));
	done
}


for i in {100..10000..100}; do
	getMemoryUsage "exp2" "Process" $i &
	proc_time=$(./bin/exp2 $i | head -n 10);
	echo "$proc_time" >> results/result.csv;

	getMemoryUsage "exp" "Thread" $i &
	thread_time=$(./bin/exp $i | head -n 10);
	echo "$thread_time" >> results/result.csv;
done;


#Rscript plot.r;
