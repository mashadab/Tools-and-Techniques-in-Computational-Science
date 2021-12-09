#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
#BATCH -o job.%j.out
#SBATCH -J job_heatcond
#SBATCH -p skx-dev
#SBATCH -A cse38018
#SBATCH -t 02:00:00

./convergence_testing.sh
