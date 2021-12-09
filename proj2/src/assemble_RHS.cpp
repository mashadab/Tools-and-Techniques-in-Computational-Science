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
double * q_1D_order2(int n, double k, double xmin, double xmax){
	timer.BeginTimer(__func__);	
	
	masa_init("heat 1D exact order 2","heateq_1d_steady_const");
	masa_set_param("A_x",2.0*Pi/(xmin-xmax));
	masa_set_param("k_0",k);
	double h = (xmin - xmax)/n;  //Length of each cell
		
	double* q = new double[n]{0.};

	for(int l = 1; l < n-1; l++){
		q[l]  = pow(h,2)*masa_eval_1d_source_t(xmin+ (l+0.5)*h)/k;
	}

	q[0]   = masa_eval_1d_exact_t(xmin+0.5*h);
	q[n-1] = masa_eval_1d_exact_t(xmax-0.5*h);
	timer.EndTimer(__func__);	
	return q;
	
}

//A matrix for 1 dimension, fourth order FD
double * q_1D_order4(int n, double k, double xmin, double xmax){
	
	timer.BeginTimer(__func__);	
	
	masa_init("heat 1D exact order 4","heateq_1d_steady_const");
	masa_set_param("A_x",2.0*Pi/(xmin-xmax));
	masa_set_param("k_0",k);
	double h = (xmin - xmax)/n;  //Length of each cell
		
	double* q = new double[n]{0.};


	for(int l = 2; l < n-2; l++){
		q[l]  = 12.0*pow(h,2)*masa_eval_1d_source_t(xmin+ (l+0.5)*h)/k;

	}
		
	q[0]   = masa_eval_1d_exact_t(xmin+0.5*h);
	q[n-1] = masa_eval_1d_exact_t(xmax-0.5*h);
	q[1]   = masa_eval_1d_exact_t(xmin+1.5*h);
	q[n-2] = masa_eval_1d_exact_t(xmax-1.5*h);
	timer.EndTimer(__func__);	
	return q;
	
}


//A matrix for 2 dimension, second order FD
double * q_2D_order2(int n, double k, double xmin, double xmax){
		
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
			//Dirichlet BC. temperature specified
		if(l % n == 0 || (l+1) % n == 0 || l / n == 0 || l / n == n-1){
			q[l] = masa_eval_2d_exact_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h);

		} 
		else{    //Source term

			q[l] = pow(h,2)*masa_eval_2d_source_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h)/k;
		}
	}	
	timer.EndTimer(__func__);	
	return q;
	
}

//A matrix for 2 dimension, second order FD
double * q_2D_order4(int n, double k, double xmin, double xmax){
		
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
			//Dirichlet BC. temperature specified: left, right, bottom, top
		if(l % n == 0 || (l+1) % n == 0 || l / n == 0 || l / n == n-1){
			q[l] = masa_eval_2d_exact_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h);
		} 
		//penultimate cell boundary conditions: left, right, bottom, top
		else if((l-1) % n == 0 || (l+2) % n == 0 || l / n == 1 || l / n == n-2){
			q[l] = masa_eval_2d_exact_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h);
		}
		else{    //Source term
			q[l] = 12.0*pow(h,2)*masa_eval_2d_source_t(xmin+(i+0.5)*h, xmin+(j+0.5)*h)/k;
		}
	}	
	timer.EndTimer(__func__);	
	return q;
	
}

//Assembling the matrix according to the input file
double * main_assemble_q(int n, int dim, int order, double k, double xmin, double xmax){

	timer.BeginTimer(__func__);	
	if(dim == 1 && order == 2){
		timer.EndTimer(__func__);	
		return q_1D_order2(n, k, xmin, xmax);
	}

	else if(dim == 1 && order == 4){
		timer.EndTimer(__func__);	
		return q_1D_order4(n, k, xmin, xmax);
	}

	else if(dim == 2 && order == 2){
		timer.EndTimer(__func__);	
		return q_2D_order2(n, k, xmin, xmax);
	}

	else if(dim == 2 && order == 4){
		timer.EndTimer(__func__);	
		return q_2D_order4(n, k, xmin, xmax);
	}

}
