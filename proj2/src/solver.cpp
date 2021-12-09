#include <grvy.h>
#include <cmath>
#include <iostream>
#include <cstring>
#include "solver.h"
#include "global_timer.h" // Bringing the GRVY_Timer_Class

#ifdef INCLUDE_PETSC
#include "petsc.h"
#endif

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



//Jacobi method for solving AT=q
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
#ifdef INCLUDE_PETSC

//PETSc (GMRES) method for solving AT=q
double *petsc(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	timer.BeginTimer(__func__);	
	double* T = new double[n]{0.0};

	PetscErrorCode ierr;
	KSP petsc_solver; 
	Mat petsc_A; 
	Vec petsc_q, petsc_T;
	PetscInt max_iter = (PetscInt) MAX_ITERS;
	PetscScalar v; 
	PetscReal tol = (PetscReal) TOL;
	KSPConvergedReason reason;

	//Creating the Petsc arrays
	ierr = MatCreate(PETSC_COMM_WORLD, &petsc_A);
	ierr = VecCreate(PETSC_COMM_WORLD, &petsc_T);
	ierr = VecCreate(PETSC_COMM_WORLD, &petsc_q);
	
	//Setting the array size
	ierr = MatSetSizes(petsc_A, PETSC_DECIDE, PETSC_DECIDE, n, n);
	ierr = VecSetSizes(petsc_T, PETSC_DECIDE, n);
	ierr = VecSetSizes(petsc_q, PETSC_DECIDE, n);

	//Setting up the matrix
	ierr = MatSetUp(petsc_A);
	ierr = VecSetUp(petsc_T);
	ierr = VecSetUp(petsc_q);

	//Converting the assembled arrays into petsc form
	for(int i = 0; i < n; i++){

		v = (PetscScalar) q[i];
		ierr = VecSetValues(petsc_q,1,&i,&v,INSERT_VALUES);
		ierr = VecSetValues(petsc_T,1,&i,&v,INSERT_VALUES); //Placeholder for computed T

		for(int j = 0; j < n; j++){
			v    = (PetscScalar) A[i][j];
			ierr = MatSetValues(petsc_A,1,&i,1,&j,&v,INSERT_VALUES);
		}


	}

	ierr = MatAssemblyBegin(petsc_A,MAT_FINAL_ASSEMBLY);
	ierr = MatAssemblyEnd(petsc_A,MAT_FINAL_ASSEMBLY);
	ierr = VecAssemblyBegin(petsc_q);
	ierr = VecAssemblyEnd(petsc_q);
	ierr = VecAssemblyBegin(petsc_T);
	ierr = VecAssemblyEnd(petsc_T);
	
	ierr = KSPCreate(PETSC_COMM_WORLD,&petsc_solver);
	ierr = KSPSetOperators(petsc_solver,petsc_A,petsc_A);
	ierr = KSPSetType(petsc_solver,KSPGMRES); //Using GMRES, which is also default in Petsc

	ierr = KSPSetTolerances(petsc_solver, tol, tol, PETSC_DEFAULT, max_iter);
	ierr = KSPSolve(petsc_solver,petsc_q,petsc_T);
	ierr = KSPGetConvergedReason(petsc_solver,&reason);

	//Convering the computed T to normal form (non-petsc)
	for(int i = 0; i < n; i++){

		ierr = VecGetValues(petsc_T,1,&i,&v);
		T[i] = (double) v;
	}
	
	//Freeing up the resources
	ierr = KSPDestroy(&petsc_solver);
	ierr = MatDestroy(&petsc_A);
	ierr = VecDestroy(&petsc_T);
	ierr = VecDestroy(&petsc_q);
	
	ierr = PetscFinalize(); //Finalizing Petsc

	timer.EndTimer(__func__);	
	return T;

}
#endif

double *main_solver(const std::string& solver_type, int l, double ** A, double * q, double eps, unsigned int MAX_ITERS){
	timer.BeginTimer(__func__);	
	std::string string1 ("Jacobi");
	std::string string2 ("Gauss-Seidel");
	std::string string3 ("Petsc");

 	//Solving AT=q
 	if(solver_type.compare(string1)==0){
		timer.EndTimer(__func__);	
        	return jacobi(l,A,q,eps,MAX_ITERS);
        }
        else if(solver_type.compare(string2)==0){
		timer.EndTimer(__func__);	
                return gauss_seidel(l,A,q,eps,MAX_ITERS);
        }
	#ifdef INCLUDE_PETSC
        else if(solver_type.compare(string3)==0){
		timer.EndTimer(__func__);	
                return petsc(l,A,q,eps,MAX_ITERS);
        }
	#endif
        else{
        std::cout<<"Wrong choice of solver. Choose either Jacobi or Gauss_Seidel or Peetsc"<<std::endl;
        
	timer.EndTimer(__func__);	
	return NULL;                                                                                 
	}
}



