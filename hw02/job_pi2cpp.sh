#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -o job_Pi2cpp.out
#SBATCH -J job_Pi2cpp
#SBATCH -p skx-dev
#SBATCH -A cse38018
#SBATCH -t 00:10:00

TIMEFORMAT=%R #To print the real time

#Comile the code to give pi2 executable (binary)

g++ -o pi2 pi.cpp

#running the executable with different inputs from the output of echo
#storing standard output of the code pi2 and standard error of time

echo 10 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
echo 100 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
echo 500 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
echo 1000 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
echo 5000 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
echo 10000 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
echo 50000 | { time ./pi2 >> pi.compiled.log;} 2>> pi.compiled.log
