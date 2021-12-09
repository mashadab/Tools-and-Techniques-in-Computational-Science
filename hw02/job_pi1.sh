#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#BATCH -o job_Pi1.%j.out
#SBATCH -J job_Pi1
#SBATCH -p skx-dev
#SBATCH -A cse38018
#SBATCH -t 00:45:00

TIMEFORMAT=%R #Getting the time value in real format

#Storing the output of ./pi.sh and stderr of time since time cmd gives output as stderr
{ time ./pi.sh 10 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 100 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 500 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 1000 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 5000 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 10000 >> pi.script.log ;} 2>> pi.script.log
{ time ./pi.sh 50000 >> pi.script.log ;} 2>> pi.script.log

