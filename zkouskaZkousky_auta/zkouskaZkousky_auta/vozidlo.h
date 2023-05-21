#include <stdio.h>

typedef struct vozidlo {
	char znacka[20];
	char model[20];
	char spz[20];
	float spotreba;
}tVozidlo;

void vypisPujcovny(char* jmSoub);
tVozidlo* nactiPujcovnu(char* pujcovna, int* dim);
void vypisVozidla(tVozidlo* poleVozidel, int dim);
tVozidlo* triMaxSpotreba();