#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <cmath>       /*math operations*/   
#include <ctime>       /* time */
#include <iostream>    /*cin and cout*/

using namespace std;  /*if something not declared in current scope, check standard*/

#define Pi 3.141592653589793238

int main ()
{
	srand(time(NULL)); 
	int N_samples=20000000; // fixing Nsamples to 960000000/48
	double x,y,z; 
	int N_i = 0, N_o; //Number of points inside the circle
	double Pi_estimate,erel;

	for (int j = 0;j < N_samples; j++){
		// Randomly picking (x,y) between 0 and 1
		x = double(rand())/double(RAND_MAX);
		y = double(rand())/double(RAND_MAX);
		z = x*x + y*y; //distance from the origin
		if(z<=1.0){
			N_i++;
		}	
	Pi_estimate = double(4*N_i)/double(N_samples); //Estimating the value of pi
	erel = fabs(Pi_estimate - Pi)/Pi; //Relative error in the estimate
	N_o  = N_samples-N_i; //Points outside the unit circle
	}
	//output
	cout<<N_samples<<" "<<N_i<<" "<<N_o<<" "<<Pi_estimate<<" "<<erel<<endl;
}
