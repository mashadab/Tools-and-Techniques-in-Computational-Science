double trap(double x0, double x2, int n)
{
    double sum = 0;
    double h = (x2 - x0) / n; // finding h base length
    for (int i = 1; i < n; i += 1) { sum += 2*y(i*h); }
    // counting of integral
    return h / 2 * (y(x0) + sum + y(x2));
 
}
