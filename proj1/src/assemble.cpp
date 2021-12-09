//Code for Matrix Assembly
//Author: Mohammad Afzal Shadab
//Email: mashadab@utexas.edu
//Date: 11/12/2020
#include <iostream>
#include <cmath>
#include <cstring>
#include "global_timer.h" // Bringing the GRVY_Timer_Class

using namespace std;

//A matrix for 1 dimension, second order FD
double ** A_1D_order2(int n){
	timer.BeginTimer(__func__);
	double** A = new double*[n];

	for(int i = 0; i < n; i++){
	
		A[i] = new double[n]{0.0}; //building the rows
	
	}

	for(int l = 1; l < n-1; l++){
		A[l][l-1] = -1.0;
		A[l][l]   =  2.0;
		A[l][l+1] = -1.0;
	}
	//Implementing the boundary conditions
	A[0][0] = 1.0;
	A[n-1][n-1] = 1.0;

	timer.EndTimer(__func__);
	return A;
	
}

//A matrix for 1 dimension, fourth order FD
double ** A_1D_order4(int n){
	
	timer.BeginTimer(__func__);
	double** A = new double*[n];

	for(int i = 0; i < n; i++){
	
		A[i] = new double[n]{0.0}; //building the rows
	
	}

	for(int l = 2; l < n-2; l++){
		
		A[l][l-2] =   1.0;
		A[l][l-1] = -16.0;
		A[l][l]   =  30.0;
		A[l][l+1] = -16.0;
		A[l][l+2] =   1.0;
	}
	//Implementing the boundary conditions
	A[0][0] = 1.0;
	A[1][1] = 1.0;
	A[n-1][n-1] = 1.0;
	A[n-2][n-2] = 1.0;

	timer.EndTimer(__func__);
	return A;
	
}

//A matrix for 2 dimensions, second order FD
double ** A_2D_order2(int n){
	timer.BeginTimer(__func__);
	int nn = n*n;
	double** A = new double*[nn];

	for(int i = 0; i < nn; i++){
	
		A[i] = new double[nn]{0.0}; //building the rows
	
	}

	for(int l = 0; l < nn; l++){
		//boundary conditions: left, right, bottom, top
		if(l % n == 0 || (l+1) % n == 0 || l / n == 0 || l / n == n-1){
			A[l][l]   =  1.0;
		} 
		else{

			A[l][l]   =  4.0;
			A[l][l+1] = -1.0;
			A[l][l-1] = -1.0;
			A[l][l+n] = -1.0;
			A[l][l-n] = -1.0;
		}	
	}

	timer.EndTimer(__func__);
	return A;
	
}

//A matrix for 2 dimensions, fourth order FD
double ** A_2D_order4(int n){
	timer.BeginTimer(__func__);
	int nn = n*n;
	double** A = new double*[nn];

	for(int i = 0; i < nn; i++){
	
		A[i] = new double[nn]{0.0}; //building the rows
	
	}

	for(int l = 0; l < nn; l++){
		//boundary conditions: left, right, bottom, top
		if(l % n == 0 || (l+1) % n == 0 || l / n == 0 || l / n == n-1){
			A[l][l]   =  1.0;
		} 
		//penultimate cell boundary conditions: left, right, bottom, top
		else if((l-1) % n == 0 || (l+2) % n == 0 || l / n == 1 || l / n == n-2){
			A[l][l]   =  1.0;
		}
		else{

			A[l][l]   =  60.0;
			A[l][l+1] = -16.0;
			A[l][l-1] = -16.0;
			A[l][l+2] =   1.0;
			A[l][l-2] =   1.0;
			A[l][l+n] = -16.0;
			A[l][l-n] = -16.0;
		      A[l][l+2*n] =   1.0;
		      A[l][l-2*n] =   1.0;
		}	
	}

	timer.EndTimer(__func__);
	return A;
	
}
//Assembling the matrix according to the input file
double ** main_assemble_A(int n, int dim, int order){

	timer.BeginTimer(__func__);
	if(dim == 1 && order == 2){
	timer.EndTimer(__func__);
		return A_1D_order2(n);
	}

	else if(dim == 1 && order == 4){
	timer.EndTimer(__func__);
		return A_1D_order4(n);
	}

	else if(dim == 2 && order == 2){
	timer.EndTimer(__func__);
		return A_2D_order2(n);
	}

	else if(dim == 2 && order == 4){
	timer.EndTimer(__func__);
		return A_2D_order4(n);
	}

}
