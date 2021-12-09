#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -o job_%j.out
#SBATCH -J integrate
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:15:00

TIMEFORMAT=%R

# If outtrap.log, outsimpson.log exits, remove the file
if [ -f temptrap.log ]; then
        rm temptrap.log
fi
if [ -f tempsimpson.log ]; then
        rm tempsimpson.log
fi

touch temptrap.log
touch tempsimpson.log

# Compiling the source code
#g++ -o ./integrate main.c
make

echo "10 1" | ./integrate >> tempsimpson.log;
echo "20 1" | ./integrate >> tempsimpson.log;
echo "50 1" | ./integrate >> tempsimpson.log;
echo "100 1" | ./integrate >> tempsimpson.log;
echo "200 1" | ./integrate >> tempsimpson.log;
echo "500 1" | ./integrate >> tempsimpson.log;
echo "1000 1" | ./integrate >> tempsimpson.log;
echo "10000 1" | ./integrate >> tempsimpson.log;
echo "10 2" | ./integrate >> temptrap.log;
echo "100 2" | ./integrate >> temptrap.log;
echo "1000 2" | ./integrate >> temptrap.log;
echo "10000 2" | ./integrate >> temptrap.log;
echo "100000 2" | ./integrate >> temptrap.log;
echo "1000000 2" | ./integrate >> temptrap.log;
echo "10000000 2" | ./integrate >> temptrap.log;
echo "100000000 2" | ./integrate >> temptrap.log;

