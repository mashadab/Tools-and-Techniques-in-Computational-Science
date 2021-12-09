#!/usr/bin/env bats
# Should you choose to use Bats for your project, I have a
# version pre-installed in my $WORK directory
# need to update your PATH to access
# export PATH=/work/00161/karl/stampede2/public/bats/bin/:$PATH
# Code is working and is in verification mode

cd ../src/

@test "verifying the successful code compilation" {

	awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=25 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat


	awk -v iter_method="Gauss-Seidel" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=2 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

}

@test "verifying if verification mode runs properly" {

	awk -v verify_mode=1 '{if($1 ~ /verify_mode/){$3 = verify_mode;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat
	run solve_heatcond
	[ "$status" -eq 0 ]

	./solve_heatcond | grep -q "VERIFICATION"
	[ "$status" -eq 0 ]
}

@test "verifying if debug mode runs properly" {

	awk -v output_mode=1 '{if($1 ~ /output_mode/){$3 = output_mode;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat
	run solve_heatcond
	[ "$status" -eq 0 ]

	./solve_heatcond | grep -q "Debug"
	[ "$status" -eq 0 ]

}

@test "verifying that the 1D, 2nd order Gauss-Seidel solver matches with reference outputs using HDF5" {

	awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=25 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v iter_method="Gauss-Seidel" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=2 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

	run h5diff -p 1e-15 data.h5 ./results/ref_sol_Gauss-Seidel_dim1_order2_n25.h5
	[ "$status" -eq 0 ]

}


@test "verifying that the 1D, 4th order Gauss-Seidel solver matches with reference outputs using HDF5" {

	awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=25 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v iter_method="Gauss-Seidel" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=4 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

	run h5diff -p 1e-15 data.h5 ./results/ref_sol_Gauss-Seidel_dim1_order4_n25.h5
	[ "$status" -eq 0 ]
}

@test "verifying that the 2D, 2nd order Gauss-Seidel solver matches with reference outputs using HDF5" {

	awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=10 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v iter_method="Gauss-Seidel" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=2 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

	run h5diff -p 1e-15 data.h5 ./results/ref_sol_Gauss-Seidel_dim2_order2_n10.h5
	[ "$status" -eq 0 ]
}

@test "verifying that the 2D, 4th order Gauss-Seidel solver matches with reference outputs using HDF5" {

	awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=10 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v iter_method="Gauss-Seidel" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=4 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

	run h5diff -p 1e-15 data.h5 ./results/ref_sol_Gauss-Seidel_dim2_order4_n10.h5
	[ "$status" -eq 0 ]
}

@test "verifying that the 1D, 2nd order Jacobi solver matches with reference outputs using HDF5" {

	awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=25 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v iter_method="Jacobi" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=2 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

	run h5diff -p 1e-15 data.h5 ./results/ref_sol_Jacobi_dim1_order2_n25.h5
	[ "$status" -eq 0 ]

}

@test "verifying that the 2D, 2nd order Jacobi solver matches with reference outputs using HDF5" {

	awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v grid=10 '{if($1 ~ /grid/){$3 = grid;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v iter_method="Jacobi" '{if($1 ~ /iter_method/){$3 = iter_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	awk -v fd_method=2 '{if($1 ~ /fd_method/){$3 = fd_method;} print $0;}' input_file.dat > input_file.tmp && mv input_file.tmp input_file.dat

	run solve_heatcond
	[ "$status" -eq 0 ]

	run h5diff -p 1e-15 data.h5 ./results/ref_sol_Jacobi_dim2_order2_n10.h5
	[ "$status" -eq 0 ]

}

