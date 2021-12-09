double simpson(double x0, double x2, int n)
{
    double sum_even = 0, sum_odd = 0;
    double h = (x2 - x0) / n; // finding h base length
    //summation of all sums
    for (int i = 1; i < n; i += 2) { sum_odd += 4*y(i*h); }
    for (int i = 2; i < n; i += 2) { sum_even += 2*y(i*h); }
    // counting of integral
    return h / 3 * (y(x0) + sum_odd + sum_even + y(x2));
}
