#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vozidlo.h"

int main() {
	vypisPujcovny("index.csv");
	int* dim = 0;
	//nactiPujcovnu("pujcovna 2",&dim);
	vypisVozidla(nactiPujcovnu("pujcovna 5", &dim),dim);
	printf("\nTri vozidla s nejvyssi spotrebou:\n");
	vypisVozidla(triMaxSpotreba(),25);
	return 0;
}