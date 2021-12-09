#!/bin/bash
#SBATCH -N 1
#SBATCH -n 48
##SBATCH -o job.log
##SBATCH -e error.%j.out
#SBATCH -J Pi3_parallel
#SBATCH -p skx-normal
#SBATCH -A cse38018
#SBATCH -t 00:10:00

SECONDS=0 # bash built-in time which initilizing everytime

#setup launcher environment
module purge
module load TACC
module load launcher 
export LAUNCHER_SCHED=interleaved
export LAUNCHER_PLUGIN_DIR=$LAUNCHER_DIR/plugins
export LAUNCHER_RMI=SLURM
export LAUNCHER_JOB_FILE=./jobfile #command which loads file to run in parallel

# If temp{i}.log files exist already, remove them and then create a new one
for((j = 1; j<=48;j++)); do
if [ -e "temp${j}.log" ]; then
  rm "temp${j}.log"
fi
touch "temp${j}.log"
done

# If iter.log exits, remove the file
if [ -f iter.log ]; then
	rm iter.log
fi

# If a.out already exists, remove it
if [ -f a.out ]; then
	rm a.out
fi

# Compiling the source code
g++ -o a.out ./pi3.cpp

TIMEFORMAT=%R ## Change time format to give only real time value, got this from stack overflow

# Tolerance is the desired accuracy
Pi=$(echo "scale =15; 3.14159265358979323" | bc -l) #Accurate value of Pi
tol=$(echo "scale=15; 0.000005" | bc -l)        #Tolerance
erel=1
iter=0 #Count number of iterations
pi_average=0 #Average value over all iterations
num_i=0 #Total number of points inside circle across all iterations
pi_iter=0 #pi value for this iteration

echo "# iter num_samples num_i pi relative_error time_accum">>iter.log

while [ 1 ]; do

	if [[ $(echo "scale=15; $erel < $tol" | bc -l) = 1 ]]; then
		break
	fi
	#empty the temp.log files before running the launcher again
	for((i = 1; i<=48;i++)); do
		>temp${i}.log
	done

	#run the launcher
	$LAUNCHER_DIR/paramrun #run the launcher
    	# update iteration number and find new value of pi_average and relative error
    	#Each core outputs to a different file to prevent race conditions.
	# awk will read from all temp* files at once, which is cool.
	iter=$(($iter+1))
	pi_iter=$(awk 'BEGIN{z=0;}{z = z + $4;}END{z = z/48.0;print z;}' temp*.log| bc -l)
    	num_i=$(($num_i+$(awk 'BEGIN{z=0;}{z = z + $2;}END{print z;}' temp*.log| bc -l)))
    	pi_average=$(echo "scale=15; ($pi_average*($iter-1)+$pi_iter)/$iter" | bc -l)
    	pi_average_2=$(echo "scale=15; 4*$num_i/$(($iter*960000000))" | bc -l)
	erel=$(echo "scale=15; (($pi_average_2-$Pi)/$Pi)" | bc -l| sed 's/-//')
	# output in required format
	echo "$iter $(($iter*960000000)) $num_i $pi_average_2 $erel $SECONDS">>iter.log
done

rm temp* # Removing all the temp.log files
