//Project 1: Main Code
//Description: This function calls all the related functions to solve 
//Author: Mohammad Afzal Shadab
//Email: mashadab@utexas.edu
//Date: 11/13/2020
#include <cstdio>
#include <math.h>
#include <grvy.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include "assemble.h"
#include "assemble_RHS.h"
#include "assemble_Texact.h"
#include "solver.h"
#include "global_timer.h"
#include "verification_debug.h"
#include "hdf5_write_output_file.h"
#include "write_output_file.h"

#ifdef INCLUDE_PETSC
#include "petsc.h"
#endif

using namespace std;
using namespace GRVY;

GRVY::GRVY_Timer_Class timer;

int main(int argc, char *argv[]){
	timer.Init("GRVY Performance timing");
	timer.BeginTimer(__func__);
	GRVY::GRVY_Input_Class parser;


	double k, xmin, xmax, eps;
	int n, dim, order, max_iter, l, verify_mode, output_mode;
	std::string solver_type; //Solver for solving AT = B: Gauss_Seidel or Jacobi
	std::string output_file; //For saving the result to output file
	
	if(! parser.Open("./input_file.dat"))
		exit(1);

	if( parser.Read_Var("mesh/dimension",&dim,0) )
		printf("--> %-11s = %i\n","dimension",dim);	

	if( parser.Read_Var("mesh/xmin",&xmin,0.0) )
		printf("--> %-11s = %f\n","xmin",xmin);

	if( parser.Read_Var("mesh/xmax",&xmax,1.0) )
		printf("--> %-11s = %f\n","xmax",xmax);
	
	if( parser.Read_Var("mesh/grid",&n,0) )
		printf("--> %-11s = %i\n","grid",n);

	if( parser.Read_Var("solver/fd_method",&order,0) )
		printf("--> %-11s = %i\n","fd_method",order);

	if( parser.Read_Var("solver/verify_mode",&verify_mode,0) )
		printf("--> %-11s = %i\n","verify_mode",verify_mode);

	if( parser.Read_Var("solver/output_mode",&output_mode,0) )
		printf("--> %-11s = %i\n","output_mode",output_mode);
	
	if( parser.Read_Var("solver/k",&k,10.0) )
		printf("--> %-11s = %f\n","k",k);

	if( parser.Read_Var("solver/iter_method",&solver_type) )
		printf("--> %-11s = %s\n","iter_method",solver_type.c_str());

	if( parser.Read_Var("solver/eps",&eps,0.0) )
		printf("--> %-11s = %f\n","eps",eps);

	if( parser.Read_Var("solver/max_iter",&max_iter,0) )
		printf("--> %-11s = %i\n","max_iter",max_iter);	

	if( parser.Read_Var("solver/output_file",&output_file) )
		printf("--> %-11s = %s\n","output_file",output_file.c_str());
		
	//Checking if the inputs the the expected values
	if(dim !=1 && dim !=2 ) std::cerr << "Invalid number of dimensions: It should be 1 or 2" << std::endl;
	if(order !=2 && order !=4 ) std::cerr << "Invalid order: It should be 2 or 4" << std::endl;
	if(n < 2 ) std::cerr << "Invalid number of cells: It should be > 2" << std::endl;
	if( xmin >= xmax ) std::cerr << "Invalid input: xmin should be less than xmax" << std::endl;
	if( k< 0.0 ) std::cerr << "Invalid value of thermal conductivity: It should be > 0" << std::endl;
	if( eps < 0.0 ) std::cerr << "Invalid value of tolerance: It should be > 0" << std::endl;
	if( max_iter < 1 ) std::cerr << "Invalid value of maximum iterations: It should be > 1" << std::endl;
		
	std::string strJacobi ("Jacobi"), strGauss("Gauss-Seidel"), strpetsc("Petsc");	
	if( solver_type.compare(strJacobi) != 0 && solver_type.compare(strGauss) != 0 && solver_type.compare(strpetsc)!= 0 ) std::cerr << "Invalid solver: It should be either Gauss-Seidel or Jacobi or Petsc" << std::endl;
	
	double h    = (xmax-xmin)/n; //cell width

	if(output_mode== 1){
		grvy_log_setlevel(GRVY_DEBUG);	
	}		
	//For dynamic memory allocation for 1D or 2D grid	
	if(dim == 1){
		l = n;
	}	
	else if(dim == 2){
		l = n*n;
	}
	double** A = new double*[l];
	for(int i = 0; i < l; i++){
		A[i] = new double[l]{0.0};
	}
	double *q = new double[l];
	double *T = new double[l];
	double *Texact = new double[l];
	double *Terr = new double[l];
	double  Terr_norm;

	//Assembling A matrix
	A = main_assemble_A(n, dim, order);  
	q = main_assemble_q(n, dim, order, k, xmin, xmax);  
	Texact = main_assemble_Texact(n, dim, order, k, xmin, xmax);  
	
	//If petsc is included then initializing
	#ifdef INCLUDE_PETSC
	PetscInitialize(&argc,&argv,0,0);
	#endif

	//Solving AT=q
	T = main_solver(solver_type,l,A,q,eps,max_iter);	

	//Verification mode check
        verification_mode(verify_mode,n,l,T,Texact);	
	
	//Debugging mode
	printing_matrix_A(l, A);
	printing_array_q(l, q);
	printing_array_T(l, T);
	printing_q_Tcomputed_Texact(l,q,Texact, T);


	//Writing the file
	hdf5_write_output(dim, l, n, xmin, xmax, h, Texact, T, output_file);
	write_output(dim, l, n, xmin, xmax, h, Texact, T, output_file);

	//Deallocating the memory
        delete[] q;
	delete[] T;
	delete[] Texact;
	delete[] Terr;
	for(int i = 0; i < l; i++){
		delete[] A[i];
	}
	delete[] A;
	timer.EndTimer(__func__);

	timer.Finalize();
	timer.Summarize();
return 0;

}
