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

for i in {100..10000..100}; do
	proc_time=$(./bin/exp2 $i 2>&1);
	thread_time=$(./bin/exp $i 2>&1);

	echo "Process,$proc_time,$i" >> results/result.csv;
	echo "Thread,$thread_time,$i" >> results/result.csv;
done;

Rscript plot.r;
