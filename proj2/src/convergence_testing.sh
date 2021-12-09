#!/bin/bash

# Code for running convergence_tests
# Author: Mohammad Afzal Shadab
# Email: mashadab@utexas.edu
# Date: 11/23/2020

# Declaring the tests we need
declare -a dimensions=(2)
declare -a iter_methods=("Petsc")
declare -a fd_methods=(2)
### To let the know that sol.dat exists and then we use it for creating reference solution
declare -a grids=(5 10 25 40 50)
### Make sure that the output file is sol.dat from the main code and input file
> sol.dat

###Now looping over dimensions, solvers, orders, and number of mesh points 
for dimension in "${dimensions[@]}"
do

	awk -v dimension=$dimension '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat


	for iter_method in "${iter_methods[@]}"
	do
		awk -v iter_method=$iter_method '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat


		for fd_method in "${fd_methods[@]}"
		do
			awk -v fd_method=$fd_method '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

			#Creating temporary empty files to store the output n L2_error Time
			>temp.log
			>output_${iter_method}_dim${dimension}_order${fd_method}.dat

			for i in "${grids[@]}"
			do
				awk -v grid=$i '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat
				
				echo "${i}, ${fd_method}, ${iter_method}, ${dimension}"

				# Running the executable								
				./solve_heatcond >> temp.log		
				
				#Copying the test results for regression testing
				cp sol.dat ./results/ref_sol_${iter_method}_dim${dimension}_order${fd_method}_n${i}.dat


			done
			echo "n	 L2_error  Time taken (s)" >> output_${iter_method}_dim${dimension}_order${fd_method}.dat
				
			awk '{if($1 == "L2"){printf("%s %s ", $7, $9 );}if($1 == "Total"){print $5;}}'  temp.log >> output_${iter_method}_dim${dimension}_order${fd_method}.dat
	
			# Moving the results to results folder
			mv output_${iter_method}_dim${dimension}_order${fd_method}.dat ./results/output_${iter_method}_dim${dimension}_order${fd_method}.dat

			# Removing the temporary file
			rm temp.log
		done
	done
done
