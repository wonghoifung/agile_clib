#include <math.h>
#include <stdlib.h>
#include "agile_geometry.h"

int agile_lint(Point p1, Point p2, Point p3, Point p4) {
	double z1, z2, z3, z4;
	int s1, s2, s3, s4;
	if (!(MAX(p1.x, p2.x) >= MIN(p3.x, p4.x) && MAX(p3.x, p4.x) >= MIN(p1.x, p2.x) && 
		MAX(p1.y, p2.y) >= MIN(p3.y, p4.y) && MAX(p3.y, p4.y) >= MIN(p1.y, p2.y))) return 0;

	if ((z1=((p3.x - p1.x) * (p2.y - p1.y)) - ((p3.y - p1.y) * (p2.x - p1.x))) < 0) {
		s1 = -1;
	} else if (z1 > 0) {
		s1 = 1;
	} else {
		s1 = 0;
	}

	if ((z2 = ((p4.x - p1.x) * (p2.y - p1.y)) - ((p4.y - p1.y) * (p2.x - p1.x))) < 0) {
		s2 = -1;
	} else if (z2 > 0) {
		s2 = 1;
	} else {
		s2 = 0;
	}

	if ((z3 = ((p1.x - p3.x) * (p4.y - p3.y)) - ((p1.y - p3.y) * (p4.x - p3.x))) < 0) {
		s3 = -1;
	} else if (z3 > 0) {
		s3 = 1;
	} else {
		s3 = 0;
	}

	if ((z4 = ((p2.x - p3.x) * (p4.y - p3.y)) - ((p2.y - p3.y) * (p4.x - p3.x))) < 0) {
		s4 = -1;
	} else if (z4 > 0) {
		s4 = 1;
	} else {
		s4 = 0;
	}

	if ((s1 * s2 <= 0) && (s3 * s4 <= 0)) return 1;
	return 0;
}

int agile_cvxhull(const agile_list* p, agile_list* polygon) {
	agile_list_element* element;
	Point* min;
	Point* low = NULL;
	Point* p0;
	Point* pi;
	Point* pc = NULL;
	double z, length1, length2;
	int count;
	min = agile_list_data(agile_list_head(p));
	for (element=agile_list_head(p); element!=NULL; element=agile_list_next(element)) {
		p0 = agile_list_data(element);
		if (p0->y < min->y) {
			min = p0;
			low = agile_list_data(element);
		} else {
			// lowest and leftmost point
			if (p0->y == min->y && p0->x < min->x) {
				min = p0;
				low = agile_list_data(element);
			}
		}
	}
	agile_list_init(polygon, NULL);
	p0 = low;
	do {
		if (agile_list_ins_next(polygon, agile_list_tail(polygon), p0) != 0) {
			agile_list_destroy(polygon);
			return -1;
		}
		count = 0;
		for (element=agile_list_head(p); element!=NULL; element=agile_list_next(element)) {
			if ((pi=agile_list_data(element))==p0) continue;
			count += 1;
			if (count == 1) {
				pc = agile_list_data(element);
				continue;
			}
			if ((z=((pi->x - p0->x) * (pc->y - p0->y)) - ((pi->y - p0->y) * (pc->x - p0->x))) > 0) {
				pc = pi;
			} else if (z==0) {
				length1 = sqrt(pow(pi->x - p0->x, 2.0) + pow(pi->y - p0->y, 2.0));
				length2 = sqrt(pow(pc->x - p0->x, 2.0) + pow(pc->y - p0->y, 2.0));
				if (length1 > length2) {
					pc = pi;
				}
			}
		}
		p0 = pc;
	} while (p0 != low);
	return 0;
}

// alpha = acos ( (x1*x2 + y1*y2 + z1*z2) / r*r )
// len = alpha * r
void agile_arclen(SPoint p1, SPoint p2, double* length) {
	Point p1_rct, p2_rct;
	double alpha, dot;

	p1_rct.x = p1.rho * sin(p1.phi) * cos(p1.theta); 
	p1_rct.y = p1.rho * sin(p1.phi) * sin(p1.theta);
	p1_rct.z = p1.rho * cos(p1.phi);

	p2_rct.x = p2.rho * sin(p2.phi) * cos(p2.theta);
	p2_rct.y = p2.rho * sin(p2.phi) * sin(p2.theta);
	p2_rct.z = p2.rho * cos(p2.phi);

	dot = (p1_rct.x * p2_rct.x) + (p1_rct.y * p2_rct.y) + (p1_rct.z * p2_rct.z);
	alpha = acos(dot / pow(p1.rho, 2.0));

	*length = alpha * p1.rho;
}

//////////////////////////////

void test_agile_geometry() {
	// TODO
}
