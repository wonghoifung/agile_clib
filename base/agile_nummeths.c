#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "agile_nummeths.h"

int interpol(const double* x, const double* fx, int n, double* z, double* pz, int m) {
	double term;
	double* table;
	double* coeff;
	int i,j,k;
	if ((table=(double*)malloc(sizeof(double)*n))==NULL) return -1;
	if ((coeff=(double*)malloc(sizeof(double)*n))==NULL) {
		free(table);
		return -1;
	}
	memcpy(table, fx, sizeof(double)*n);
	coeff[0] = table[0];
	for (k=1; k<n; ++k) {
		for (i=0; i<n-k; ++i) {
			j=i+k;
			table[i] = (table[i+1]-table[i]) / (x[j]-x[i]);
		}
		coeff[k] = table[0];
	}
	free(table);
	for (k=0; k<m; ++k) {
		pz[k] = coeff[0];
		for (j=1; j<n; ++j) {
			term = coeff[j];
			for (i=0; i<j; ++i) {
				term = term * (z[k] - x[i]);
			}
			pz[k] = pz[k] + term;
		}
	}
	free(coeff);
	return 0;
}

void lsqe(const double* x, const double* y, int n, double* b1, double* b0) {
	double sumx, sumy, sumx2, sumxy;
	int i;
	sumx = 0.0;
	sumy = 0.0;
	sumx2 = 0.0;
	sumxy = 0.0;
	for (i=0;i<n;++i) {
		sumx += x[i];
		sumy += y[i];
		sumx2 += pow(x[i],2.0);
		sumxy += (x[i] * y[i]);
	}
	*b1 = (sumxy - sumx * sumy / (double)n) / (sumx2 - pow(sumx,2.0) / (double)n);
	*b0 = (sumy - (*b1 * sumx)) / (double)n;
}

//////////////////////////////

#include <stdio.h>

void test_agile_nummeths() {
	double x[4] = {-3.0, -2.0, 2.0, 3.0};
	double fx[4] = {-5.0, -1.1, 1.9, 4.8};
	double z[3] = {-2.5, 0.0, 2.5};
	double pz[3];
	interpol(x, fx, 4, z, pz, 3);
	for (int i=0; i<3; ++i) printf("%.3f ",pz[i]);
	printf("\n");

	double xi[9] = {-4.0, -3.0, -2.0, -1.5, -0.5, 1.0, 2.0, 3.5, 4.0};
	double yi[9] = {-3.0, -1.0, -2.0, -0.5, 1.0, 0.0, 1.5, 1.0, 2.5};
	double b1,b0;
	lsqe(xi, yi, 9, &b1, &b0);
	printf("%.4f %.4f\n", b1, b0);
}
