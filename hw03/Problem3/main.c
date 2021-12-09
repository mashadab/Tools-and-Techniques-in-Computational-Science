#include <iostream>
#include <math.h>
#include "func.h"
#include "trapezoidal.h"
#include "simpson.h"

using namespace std;  //checks std if something is undeclared

#define Pi 3.141592653589793238  //accurate value of pi upto 18 places of decimal
#define erf_tab 0.84270079295    //Error     

int main()
{
    double a = 0.0, b = 1.0, f = 0;
    int n;
    int method;
    cin >> n; 
    cin >> method;     //commandline input the number of the strips   
    //cin >> method;//commandline input the method used 0:simpson, 1:trapezoidal
    double dx = (b-a)/n;
    
    if( method == 1 ) {   //For simpson rule choose 1
    	if( n%2 == 0 ){
        	f = simpson(a, b, n);
	}
    	 else {
		f = simpson(a, b-dx, n - 1) + dx/6*( y(b-dx) + 4*y((2*b-dx)/2) + y(b) );
     }} else if ( method == 2 ) {   //For trapezoidal rule choose 1
        if( n%2 == 0 ) {
                f = trap(a, b, n);
        }
         else {
                f = trap(a, b-dx, n - 1) + dx/2*( y(b-dx) + 2*y((2*b-dx)/2) + y(b) );
        }}

// Result
    f = 2.0 / sqrt(Pi) * f;
    double erel = fabs(f - erf_tab)/erf_tab;
    cout.precision(15);
    cout<< n <<" "<<f<<" "<<erel<<" "<<endl;
}


