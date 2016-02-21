#ifndef agile_nummeths_header
#define agile_nummeths_header

int interpol(const double* x, const double* fx, int n, double* z, double* pz, int m);
void lsqe(const double* x, const double* y, int n, double* b1, double* b0);
int root(double(*f)(double), double(*g)(double), double* x, int* n, double delta);

void test_agile_nummeths();

#endif
