//Code for Matrix Assembly
//Author: Mohammad Afzal Shadab
//Email: mashadab@utexas.edu
//Date: 11/12/2020
#include <iostream>
#include <cmath>
#include <grvy.h>
#include <cstring>
#include "global_timer.h" // Bringing the GRVY_Timer_Class
#include "solver.h"
#include "verification_debug.h"

using namespace std;

//A matrix for 1 dimension, second order FD
double verification_mode(int verify_mode, int n,int l, double *T, double *Texact){
	timer.BeginTimer(__func__);
	double* Terr = new double[l]{0.0};
	double Terr_norm;
	
	//Check if verification mode is on i.e. 1.

        //Error in computed minus the analytical value
	if(verify_mode==1){
		
		std::cout << "--------> VERIFICATION MODE <--------" << std::endl;
		for(int i = 0; i < l; i++){
			Terr[i] = T[i] - Texact[i];	
		}
		Terr_norm = L2_norm(l,Terr);
		std::cout << "L2 Norm of error for n "<<n<<" is "<<Terr_norm << std::endl;
	}
	timer.EndTimer(__func__);
	return NULL;
		
}

//Printing the matrix A
void printing_matrix_A(int n, double ** A){
	
	timer.BeginTimer(__func__);
	grvy_printf(GRVY_DEBUG, "\n");
	grvy_printf(GRVY_DEBUG, "Debug Mode - printing A");
	grvy_printf(GRVY_DEBUG, "A = [");

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			grvy_printf(GRVY_DEBUG, "%.0f ", A[i][j]);
		}	
		grvy_printf(GRVY_DEBUG, ";\n");
	}
	grvy_printf(GRVY_DEBUG, "]\n");
	timer.EndTimer(__func__);
}

//Printing the matrix q
void printing_array_q(int n, double * q){
	
	timer.BeginTimer(__func__);
	grvy_printf(GRVY_DEBUG, "\n");
	grvy_printf(GRVY_DEBUG, "Debug Mode - printing q \n");
	grvy_printf(GRVY_DEBUG, "q = [");

	for(int i = 0; i < n; i++){
		grvy_printf(GRVY_DEBUG, "%.0f ", q[i]);
		grvy_printf(GRVY_DEBUG, ";\n");
	}
	grvy_printf(GRVY_DEBUG, "]\n");
	timer.EndTimer(__func__);
}

//Printing the matrix T computed and exact
void printing_q_Tcomputed_Texact(int n, double * q, double * T_exact, double * T_computed){
	
	timer.BeginTimer(__func__);
	grvy_printf(GRVY_DEBUG, "\n");
	grvy_printf(GRVY_DEBUG, "Debug Mode - printing Texact Tcomputed \n");
	grvy_printf(GRVY_DEBUG, "%-11s	%-11s	%-11s\n","q","T_exact[C]","T_computed [C]");

	for(int i = 0; i < n; i++){
		grvy_printf(GRVY_DEBUG, "%-11f	%-11f	%-11f\n",q[i],T_exact[i],T_computed[i]);
	}
	grvy_printf(GRVY_DEBUG, "]\n");
	timer.EndTimer(__func__);
}

//Printing the matrix exact T
void printing_array_T(int n, double * T){
	
	timer.BeginTimer(__func__);
	grvy_printf(GRVY_DEBUG, "\n");
	grvy_printf(GRVY_DEBUG, "Debug Mode - printing T \n");
	grvy_printf(GRVY_DEBUG, "T = [");

	for(int i = 0; i < n; i++){
		grvy_printf(GRVY_DEBUG, "%.0f ", T[i]);
		grvy_printf(GRVY_DEBUG, ";\n");
	}
	grvy_printf(GRVY_DEBUG, "]\n");
	timer.EndTimer(__func__);
}
