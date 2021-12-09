#include <grvy.h>
#include <cmath>
#include <iostream>
#include <cstring>
#include "solver.h"
#include "global_timer.h" // Bringing the GRVY_Timer_Class
using namespace std;

// Having the L2 norm from the definition given on Canvas
double L2_norm(int n, double *x){
	timer.BeginTimer(__func__);	
	double norm = 0;

	for(int i = 0; i < n; i++){
		norm += pow(x[i], 2);	
	}

	norm *= 1.0/n;
	norm = pow(norm, 0.5);

	timer.EndTimer(__func__);	
	return norm;
}

//Solvers
//Gauss-Seidel method for solving AT=q
double *gauss_seidel(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	timer.BeginTimer(__func__);	
	unsigned int iters = 0;
	double error = 0.0;
	double* T = new double[n]{0.0};
	double T_old[n];
	double delta_T[n];

	while (iters < MAX_ITERS){


		// Set T_old equal to T from previous iteration
		for (int i = 0; i < n; i++){
			T_old[i] = T[i];
		}

		for (int i = 0; i < n; i++){
			T[i] = q[i];
			double sum = 0.0;
		
			// T has been updated
			
			for (int j = 0; j < i; j++){
				sum += A[i][j] * T[j];
			}

			for (int j = i+1; j < n; j++){
				sum += A[i][j] * T[j];
			}
			
			T[i] = T[i] - sum;
			T[i] = T[i] / A[i][i];
			delta_T[i] = T[i] - T_old[i];


		} 
		//L2 norm for error from Karls' notes
		//
		error = L2_norm(n,delta_T)/L2_norm(n,T);

		iters = iters + 1;
		if (error <= TOL){
			break;
		}		
    	}	

	timer.EndTimer(__func__);	
	return T;

}



//Gauss-Seidel method for solving AT=q
double *jacobi(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	timer.BeginTimer(__func__);	
	unsigned int iters = 0;
	double error = 0.0;
	double* T = new double[n]{0.0};
	double T_old[n];
	double delta_T[n];

	while (iters < MAX_ITERS){


		// Set T_old equal to T from previous iteration
		for (int i = 0; i < n; i++){
			T_old[i] = T[i];
		}

		for (int i = 0; i < n; i++){
			T[i] = q[i];
			double sum = 0.0;
		
			// T has been updated
			
			for (int j = 0; j < i; j++){
				sum += A[i][j] * T_old[j];
			}

			for (int j = i+1; j < n; j++){
				sum += A[i][j] * T_old[j];
			}
			
			T[i] = T[i] - sum;
			T[i] = T[i] / A[i][i];
			delta_T[i] = T[i] - T_old[i];

		} 
		//L2 norm for error from Karls' notes
		//
		error = L2_norm(n,delta_T)/L2_norm(n,T);

		iters = iters + 1;
		if (error <= TOL){
			break;
		}		
    	}	

	timer.EndTimer(__func__);	
	return T;

}

double *main_solver(const std::string& solver_type, int l, double ** A, double * q, double eps, unsigned int MAX_ITERS){
	timer.BeginTimer(__func__);	
	std::string string1 ("Jacobi");
	std::string string2 ("Gauss-Seidel");

 	//Solving AT=q
 	if(solver_type.compare(string1)==0){
		timer.EndTimer(__func__);	
        	return jacobi(l,A,q,eps,MAX_ITERS);
        }
        else if(solver_type.compare(string2)==0){
		timer.EndTimer(__func__);	
                 return gauss_seidel(l,A,q,eps,MAX_ITERS);
        }
        else{
        std::cout<<"Wrong choice of solver. Choose either Jacobi or Gauss_Seidel"<<std::endl;
        
	timer.EndTimer(__func__);	
	return NULL;                                                                                 
	}
}



