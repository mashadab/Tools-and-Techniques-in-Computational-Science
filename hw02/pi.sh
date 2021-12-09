#Q4: Calulating the value of pi
#    using Monte Carlo method

#!/bin/bash

N_sample=$1 #iterations for Monte-Carlo simulation
N_i=0          #points inside circle
do
        x=$(echo "scale=15; $RANDOM/32767" | bc -l)
        y=$(echo "scale=15; $RANDOM/32767" | bc -l)
        z=$(echo "scale=15; sqrt($x^2 + $y^2)" | bc)
        if(( $(echo "$z <= 1." | bc -l) )); then
                N_i=$(($N_i+1))
        fi
done
N_o=$(($N_sample - $N_i))
pi_estimate=$(echo "scale=15; 4.*$N_i/$N_sample" | bc)
pi_accurate=$(echo "scale=15; 4.*a(1)" | bc -l)
e_rel=$(echo $"scale=15; ($pi_estimate - $pi_accurate)/($pi_accurate)" | bc -l | sed 's/-//')
 #sed is used to remove negative values
echo -n "$N_sample $N_i $N_o $pi_estimate $e_rel "






