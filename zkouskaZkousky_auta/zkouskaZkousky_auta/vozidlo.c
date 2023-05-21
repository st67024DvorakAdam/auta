#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vozidlo.h"

void vypisPujcovny(char* jmSoub) {
	FILE* file = fopen(jmSoub, "r");
	if (file == NULL) {
		perror("Chyba pri otevreni souboru");
		exit(1);
	}
	char line[1024];

	if (fgets(line, 1024, file) == NULL) {
		perror("Nelze nacist hlavicku ze souboru");
		exit(1);
	}

	printf("Seznam pujcoven:\n");
	while (fgets(line, 1024, file) != NULL) {
		char* token = strtok(line, ";");
		printf("%s\n", token);
	}
	printf("\n");

	fclose(file);
}
tVozidlo* nactiPujcovnu(char* pujcovna, int* dim) {
	int pocet;
	int offset;

	tVozidlo* poleVozidel;

	//zjiötÏnÌ vÌce info o p˘jËovnÏ z data.csv
	FILE* file = fopen("index.csv", "r");
	if (file == NULL) {
		perror("Chyba pri otevreni souboru");
		exit(1);
	}
	char line[1024];

	if (fgets(line, 1024, file) == NULL) {
		perror("Nelze nacist hlavicku ze souboru");
		exit(1);
	}

	while (fgets(line, 1024, file) != NULL) {
		char* token = strtok(line, ";");
		if (strcmp(token, pujcovna) == 0) {
			token = strtok(NULL, ";");
			pocet = (int)strtol(token, NULL, 10);

			token = strtok(NULL, ";");
			offset = (int)strtol(token, NULL, 10);
			break;
		}
	}
	fclose(file);
	//konec sekce kde zjiöùuji offset a pocet

	*dim = pocet;
	poleVozidel = (tVozidlo*)malloc(pocet * sizeof(tVozidlo));

	//cteni aut dannÈ p˘jËovny z bin souboru
	FILE* binFile = fopen("data.bin", "rb");
	if (binFile == NULL) {
		perror("Chyba pri otevirani binarniho souboru");
		exit(1);
	}

	fseek(binFile, ((long)offset), 0);

	tVozidlo currentVozidlo;
	float* token = (float*)malloc(sizeof(float));
	for (int i = 0; i < pocet; i++)
	{
		fread(currentVozidlo.znacka, sizeof(char), 20, binFile);
		fread(currentVozidlo.model, sizeof(char), 20, binFile);
		fread(currentVozidlo.spz, sizeof(char), 20, binFile);
		fread(token, sizeof(float), 1, binFile);
		currentVozidlo.spotreba = token[0];
		poleVozidel[i] = currentVozidlo;
	}
	fclose(binFile);

	return poleVozidel;
}
void vypisVozidla(tVozidlo* poleVozidel, int dim) {
	printf("\nVypis vozidel:\n");
	for (int i = 0; i < dim; i++)
	{
		printf("%s\t%s\t%s\t%f\n",
			poleVozidel[i].znacka,
			poleVozidel[i].model,
			poleVozidel[i].spz,
			poleVozidel[i].spotreba
			);
	}
}

int compareBySpotreba(tVozidlo v1, tVozidlo v2) {
	if (v1.spotreba > v2.spotreba) {
		return -1;
	}
	else {
		return 1;
	}
}

tVozidlo* triMaxSpotreba() {
	//zjiötÏnÌ poctu aut z data.csv
	FILE* file = fopen("index.csv", "r");
	if (file == NULL) {
		perror("Chyba pri otevreni souboru");
		exit(1);
	}
	char line[1024];

	if (fgets(line, 1024, file) == NULL) {
		perror("Nelze nacist hlavicku ze souboru");
		exit(1);
	}

	int pocet = 0;
	while (fgets(line, 1024, file) != NULL) {
		char* token = strtok(line, ";");
			token = strtok(NULL, ";");
			pocet += (int)strtol(token, NULL, 10);
	}
	fclose(file);
	//konec sekce kde zjiöùuji pocet aut

	tVozidlo* poleVozidel = (tVozidlo*)malloc(pocet * sizeof(tVozidlo));

	//naËÌt·nÌ vozidel
	FILE* binFile = fopen("data.bin", "rb");
	if (binFile == NULL) {
		perror("Chyba pri otevirani binarniho souboru");
		exit(1);
	}

	tVozidlo currentVozidlo;
	float* token = (float*)malloc(sizeof(float));
	for (int i = 0; i < pocet; i++)
	{
		fread(currentVozidlo.znacka, sizeof(char), 20, binFile);
		fread(currentVozidlo.model, sizeof(char), 20, binFile);
		fread(currentVozidlo.spz, sizeof(char), 20, binFile);
		fread(token, sizeof(float), 1, binFile);
		currentVozidlo.spotreba = token[0];
		poleVozidel[i] = currentVozidlo;
	}
	fclose(binFile);


	qsort(poleVozidel, pocet, sizeof(tVozidlo), compareBySpotreba);

	tVozidlo* setridenePole = (tVozidlo*)malloc(3 * sizeof(tVozidlo));
	memcpy(setridenePole, poleVozidel, 3*sizeof(tVozidlo));

	return setridenePole;
}