//Code for writing output file using HDF5
//Author: Mohammad Afzal Shadab
//Email: mashadab@utexas.edu
//Date: 12/7/2020
#include <fstream>
#include <cmath>
#include <grvy.h>
#include <cstring>
#include "global_timer.h" // Bringing the GRVY_Timer_Class
#include "solver.h"
#include "hdf5_write_output_file.h"
#include "hdf5.h"
using namespace std;

void hdf5_write_output(int dim, int l, int n ,double xmin, double xmax, double h, double * Texact, double * T, std::string output_file){
	timer.BeginTimer(__func__);	

	int * narray   = new int[1]{n};
	int * dimarray = new int[1]{dim};
	double* x = new double[l]{0.};	
	double* y = new double[l]{0.};	

	hid_t		file, dataset1,dataset2, dataspace1, dataspace2;//file and dataset handles
	hsize_t		dim1[0], dim2[0];				//dataset dimensions
	herr_t		status1, status2, status3, status4, status5, status6;

	//Data accumulation
	if(dim==1){
		//Calculating x array
		for(int i = 0; i < l; i++){
			x[i]= xmin+(i+0.5)*h;
		}
	}
	else if(dim==2){
		int ii, jj;			
		//Calculating x and y array
		for(int i = 0; i < l; i++){
			ii  = i%n;
			jj  = i/n;
		        x[i]=xmin+(ii+0.5)*h; 
			y[i]=xmin+(jj+0.5)*h;
		}
	}
	
	//Create a new HDF5 file with default properties
	file = H5Fcreate("data.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	//Create dataset for fixed size dataset
	dim1[0] = l;
	dataspace1 = H5Screate_simple(1,dim1, NULL);

	//Create dataset using defined dataspace and default properties (store native ints_
	dataset1 = H5Dcreate(file, "T computed [C]", H5T_NATIVE_DOUBLE, dataspace1, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	
	//Write the data to the dataset using default transfer properties
	status1  = H5Dwrite(dataset1, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, T);
	
	//Create dataset for fixed size dataset
	dim1[0] = l;
	dataspace1 = H5Screate_simple(1,dim1, NULL);

	//Create dataset using defined dataspace and default properties (store native ints_
	dataset1 = H5Dcreate(file, "T exact [C]", H5T_NATIVE_DOUBLE, dataspace1, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	
	//Write the data to the dataset using default transfer properties
	status2  = H5Dwrite(dataset1, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, Texact);

	//Create dataset for fixed size dataset
	dim1[0] = l;
	dataspace1 = H5Screate_simple(1,dim1, NULL);

	//Create dataset using defined dataspace and default properties (store native ints_
	dataset1 = H5Dcreate(file, "x [m]", H5T_NATIVE_DOUBLE, dataspace1, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	
	//Write the data to the dataset using default transfer properties
	status3  = H5Dwrite(dataset1, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, x);

	if(dim==2){
		//Create dataset for fixed size dataset
		dim1[0] = l;
		dataspace1 = H5Screate_simple(1,dim1, NULL);
	
		//Create dataset using defined dataspace and default properties (store native ints_
		dataset1 = H5Dcreate(file, "y [m]", H5T_NATIVE_DOUBLE, dataspace1, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	
		//Write the data to the dataset using default transfer properties
		status4  = H5Dwrite(dataset1, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, y);
	}


	//Create dataset for fixed size dataset
	dim2[0] = 1;
	dataspace2 = H5Screate_simple(1,dim2, NULL);
	
	//Create dataset using defined dataspace and default properties (store native ints_
	dataset2 = H5Dcreate(file, "N", H5T_NATIVE_INT, dataspace2, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	
	//Write the data to the dataset using default transfer properties
	status5  = H5Dwrite(dataset2, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, narray);

	
	//Create dataset for fixed size dataset
	dim2[0] = 1;
	dataspace2 = H5Screate_simple(1,dim2, NULL);
	
	//Create dataset using defined dataspace and default properties (store native ints_
	dataset2 = H5Dcreate(file, "Dimension", H5T_NATIVE_INT, dataspace2, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	
	//Write the data to the dataset using default transfer properties
	status6  = H5Dwrite(dataset2, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dimarray);
	
	//Releasing the resources
	H5Sclose(dataspace1);
	H5Dclose(dataset1);
	H5Sclose(dataspace2);
	H5Dclose(dataset2);
	H5Fclose(file);

	timer.EndTimer(__func__);
}

