#!/bin/bash

if [ ! -d "bin" ]; then
	mkdir bin;
fi

if [ ! -d "results" ]; then
	mkdir results;
fi

gcc -pthread -o bin/exp exp.c;
gcc exp2.c -o bin/exp2;

echo "structure,time,sample" > results/result.csv;
echo "structure,usage,sample" > results/result_men.csv;

function getMemoryUsage() {
	while [ 0 ] ; do
		sleep 0.3;
		sum=$(ps av | grep "./bin/$1" | awk '{sum+=$8}END{print sum}');
		echo "$2,$sum,$3" >> results/result_men.csv
	done
}


for i in {100..10000..100}; do
	getMemoryUsage "exp2" "Process" $i &
	pid=$!;
	proc_time=$(./bin/exp2 $i 2>&1);
	echo "Process,$proc_time,$i" >> results/result.csv;
	kill $pid 12> /dev/null;

	getMemoryUsage "exp" "Thread" $i &
	pid=$!;
	thread_time=$(./bin/exp $i 2>&1);
	echo "Thread,$thread_time,$i" >> results/result.csv;
	kill $pid 12> /dev/null;
done;


#Rscript plot.r;
