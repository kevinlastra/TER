#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Comparer.h"

using namespace std;

char ligne1[256], ligne2[256];

void Comparer::Compare(const char* fichier1,const char* fichier2)
{
	fstream base(fichier1), resultat(fichier2);
	int i; i = 0;
	
	while(!resultat.eof())
	{
		base.getline(ligne1,256);
		resultat.getline(ligne2,256);
		i++;
		if(strcmp(ligne1,ligne2) != 0)
		{
			cout << "différence sur la ligne : "<< i << endl;
		}
	}
}