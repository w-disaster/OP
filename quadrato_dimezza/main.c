#include <stdio.h>
#include <stdlib.h>
#include "quadrato.h"
#include "dimezza.h"
#include <math.h>

double salva;

int main(){
	salva = power(halfcos(13.17));
	printf("%f ", salva);
	return 0;
}
