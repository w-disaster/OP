#include <stdio.h>
#include <math.h>
#include "dimezza.h"

extern double salva;

double halfcos(double x){
	 salva = cos(x)/2;
	 return salva;
}

