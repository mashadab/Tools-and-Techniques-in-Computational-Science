//Code for Matrix Assembly
//Author: Mohammad Afzal Shadab
//Email: mashadab@utexas.edu
//Date: 11/12/2020

#include <iostream>
#include <cmath>
#include <cstring>
#include <masa.h>
#include "global_timer.h"

using namespace std;

#define Pi 3.141592653589793238  //accurate value of pi upto 18 places of decimal

//A matrix for 1 dimension, second order FD
double * Texact_1D_order2(int n, double k, double xmin, double xmax){
	
	timer.BeginTimer(__func__);	
	
	masa_init("heat 1D exact order 2","heateq_1d_steady_const");
	masa_set_param("A_x",2.0*Pi/(xmin-xmax));
	masa_set_param("k_0",k);
	double h = (xmin - xmax)/n;  //Length of each cell
		
	double* q = new double[n]{0.};

	for(int l = 0; l < n; l++){
		q[l]  = masa_eval_1d_exact_t(xmin+ (l+0.5)*h);
	}
	timer.EndTimer(__func__);	
	return q;
	
}

//A matrix for 1 dimension, fourth order FD
double * Texact_1D_order4(int n, double k, double xmin, double xmax){
	
	timer.BeginTimer(__func__);	
	
	masa_init("heat 1D exact order 4","heateq_1d_steady_const");
	masa_set_param("A_x",2.0*Pi/(xmin-xmax));
	masa_set_param("k_0",k);
	double h = (xmin - xmax)/n;  //Length of each cell
		
	double* q = new double[n]{0.};


	for(int l = 0; l < n; l++){
		q[l]  = masa_eval_1d_exact_t(xmin+ (l+0.5)*h);

	}
	timer.EndTimer(__func__);	
	return q;
	
}


//A matrix for 2 dimension, second order FD
double * Texact_2D_order2(int n, double k, double xmin, double xmax){
		
	timer.BeginTimer(__func__);	
	masa_init("heat 2D exact order 2","heateq_2d_steady_const");
	masa_set_param("A_x",2.0*Pi/(xmin-xmax));
	masa_set_param("B_y",2.0*Pi/(xmin-xmax));
	masa_set_param("k_0",k);
	double h = (xmin - xmax)/n;  //Length of each cell
		
	int nn = n*n;
	double* q = new double[nn]{0.};

	for(int l = 0; l < nn; l++){
		int i = l % n;
		int j = l / n;

		q[l] = masa_eval_2d_exact_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h);
	}	
	timer.EndTimer(__func__);	
	return q;
}

//A matrix for 2 dimension, second order FD
double * Texact_2D_order4(int n, double k, double xmin, double xmax){
		
	timer.BeginTimer(__func__);	
	masa_init("heat 2D exact order 4","heateq_2d_steady_const");
	masa_set_param("A_x",2.0*Pi/(xmin-xmax));
	masa_set_param("B_y",2.0*Pi/(xmin-xmax));
	masa_set_param("k_0",k);
	double h = (xmin - xmax)/n;  //Length of each cell
		
	int nn = n*n;
	double* q = new double[nn]{0.};

	for(int l = 0; l < nn; l++){
		int i = l % n;
		int j = l / n;
		q[l]  = masa_eval_2d_exact_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h);
	}
	timer.EndTimer(__func__);	
	return q;
	
}

//Assembling the matrix according to the input file
double * main_assemble_Texact(int n, int dim, int order, double k, double xmin, double xmax){

	timer.BeginTimer(__func__);	
	//timer.StartTimer(__func__);	
	if(dim == 1 && order == 2){
		timer.EndTimer(__func__);	
		return Texact_1D_order2(n, k, xmin, xmax);
	}

	else if(dim == 1 && order == 4){
		timer.EndTimer(__func__);	
		return Texact_1D_order4(n, k, xmin, xmax);
	}

	else if(dim == 2 && order == 2){
		timer.EndTimer(__func__);	
		return Texact_2D_order2(n, k, xmin, xmax);
	}

	else if(dim == 2 && order == 4){
		timer.EndTimer(__func__);	
		return Texact_2D_order4(n, k, xmin, xmax);
	}

}
