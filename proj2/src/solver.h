double L2_norm(int n, double *x);
double *gauss_seidel(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
double *jacobi(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
double *petsc(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
double *main_solver(const std::string& solver, int l, double ** A, double * q, double eps, unsigned int
 MAX_ITERS);




