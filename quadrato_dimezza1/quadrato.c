#include <stdio.h>
#include "quadrato.h"

extern double salva;

double power(double x){
	salva = x*x;
	return salva;
}
