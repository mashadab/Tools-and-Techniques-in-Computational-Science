#include<cstdio>   // Standard input, output: NULL, printf //
#include<cstdlib>  //Standard libraries: rand, srand //
#include<cmath>    //Math library //
#include<ctime>    //Time measurement: time //
#include<iostream> //Input, output streaming*: cin, cout //

using namespace std; //checks std if something is undeclared

int main()
{
        srand(time(NULL));    //seed based on current time
        int N_sample;
        cin>>N_sample;       //Number of samples input
        double x,y,z; //Coordinates & distance variables
        double pi_accurate,pi_estimate,erel; //Pi value: accurate, estimate; relative err
        int N_i,N_o;       //Counter for points inside and outside the circle

        N_i = 0; //initialization
        for (int i = 0;i<N_sample;i++){
                // Generating random number between 0 and 1: for x, y coordinates
                x = double(rand())/double(RAND_MAX);
                y = double(rand())/double(RAND_MAX);
                z = x*x + y*y; //Distance from origin
                if(z<=1.0){
                        N_i++;  //Increase counter by 1 if (x,y) lie in unit circle
                }
       //Pi and relative error estimation
        pi_estimate = double(4*N_i)/double(N_sample);
        erel = fabs(pi_estimate - 4.0*atan(1.0))/(4.0*atan(1.0));
        N_o = N_sample - N_i;
        }
	//Output
	cout<<N_sample<<" "<<N_i<<" "<<N_o<<" "<<pi_estimate<<" "<<erel<<" ";
}
