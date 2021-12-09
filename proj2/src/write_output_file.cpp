//Code for Matrix Assembly
//Author: Mohammad Afzal Shadab
//Email: mashadab@utexas.edu
//Date: 11/12/2020
#include <iostream>
#include <fstream>
#include <cmath>
#include <grvy.h>
#include <cstring>
#include "global_timer.h" // Bringing the GRVY_Timer_Class
#include "solver.h"
#include "write_output_file.h"

using namespace std;

void write_output(int dim, int l, int n ,double xmin, double xmax, double h, double * Texact, double * T, std::string output_file){
	//std::string output_file = "sol.dat";

	if(dim==1){
		//Writing to an output file
		std::ofstream outputfile (output_file);
		if (outputfile.is_open()){
			outputfile << "#x [m]" << std::fixed<<"T Exact [C]"<<std::fixed<<"T Computed [C]" <<std::endl;	
			for(int i = 0; i < l; i++){
			outputfile << xmin+(i+0.5)*h << " " << std::fixed << Texact[i] << " " << std::fixed << T[i] << std::endl;
			}
		outputfile.close();	
		}
	}
	else if(dim==2){
		int ii, jj;			
		//Writing to an output file
		std::ofstream outputfile (output_file);
		if (outputfile.is_open()){
			outputfile << "#x [m]	   "<< "#y [m]" << std::fixed<<"T Exact [C]   "<<std::fixed<<"T Computed [C]" <<std::endl;	
			for(int i = 0; i < l; i++){
				ii = i%n;
				jj = i/n;
			outputfile << xmin+(ii+0.5)*h << " " << std::fixed << xmin+(jj+0.5)*h << " " << std::fixed << Texact[i] << " " << std::fixed << T[i] << std::endl;
			}
		outputfile.close();	
		}
	}
}
