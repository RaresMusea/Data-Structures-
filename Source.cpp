#include "Pair.h"
#include "SortArray.h"
#include<iostream>

//Functie recursiva ce calculeaza cel mai mare divizor comun a doua numere utilizand algoritmul lui Stein
int Stein(int a, int b) {
	//Situatiile in care numerele sunt egale sau nule
	if (a == 0) return b;
	if (b == 0) return a;
	if (a == b) return a;

	//Daca prima valoare este para si a doua impara
	if (a % 2 == 0 && b % 2 == 1)
		return Stein(a / 2, b);

	//Daca ambele valori sunt pare
	if (a % 2 == 0 && b % 2 == 0)
		return 2 * Stein(a / 2, b / 2);

	//Daca prima valoare este impara si a doua para
	if (a % 2 == 1 && b % 2 == 0)
		return Stein(a, b / 2);

	//Reducerea numerelor mari prin scaderi, la recursie
	if (a > b)
		return Stein(((a - b) / 2), b);
	return Stein(((b - a) / 2), a);
}




//Afiseaza sirul Farey de ordin n
void displayFareySequence(SortArray<Fraction>result) {

	for (int i=0; i<result.getSize(); i++) {

		if(i!=result.getSize()-1)
		cout << "(" << result[i].getNumerator() << " / " << result[i].getDenominator() << "), ";
		else
			cout << "(" << result[i].getNumerator() << " / " << result[i].getDenominator() << ")";

	}

}


//Functie care genereaza sirul lui Farey de ordin n si ulterior apeleaza functia de mai sus, pentru a il afisa
void FareySequence(int n) {
	

	//Vector de instante ale clasei Fraction, in care vom stoca sirul lui Farey de ordin n
	SortArray<Fraction> result;

	//Adaugam la sirul lui Farey elementele 0/1, respectiv 1/1;
	result.addValue(Fraction(0,1));

	//Adaugam restul elementelor
	for(int i=1;i<=n;i++)
		for(int j=1+i;j<=n;j++)
			//Pentru sirul lui Farey, ne asiguram ca adaugam doar elemente ce sunt prime intre ele (cel mai mare divizor comun este 1)
			if (Stein(i, j) == 1) {
				Fraction f(i, j);
				result.addValue(f);
			}
	result.addValue(Fraction(1,1));
	//Afisam secventa
	cout << "Sirul Farey de ordin " << n << '\n';
	displayFareySequence(result);

}

int main() {

	//Citire dimensiune si apel metode
	
	
	int dim;
	cout << "Introduceti ordinul sirului Farey: "; cin >> dim;
	FareySequence(dim);
	return 0;

	





}
