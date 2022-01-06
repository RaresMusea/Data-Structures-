#pragma once

//Fisier Pair.h, in care vom defini clasa Fraction, in care vom retine numaratorul si respectiv numitorul unei fractii, istanta ce ulteror va fi utilizata pentru implementarea sirului lui Farey
class Fraction {

private:

	//Numaratorul
	int numerator;
	//Numitorul
	int denominator;

public:
	//Constructor implicit
	Fraction();

	//Constructor inline de initializare
	Fraction(int num, int den);

	//Constructor de copiere
	Fraction(Fraction const&f);


	//Getters:
	int getNumerator() { return this->numerator; }

	int getDenominator() { return this->denominator; }

	//Setters
	void setNumerator(int numerator) { this->numerator = numerator; }

	void setDenominator(int denominator) { this->denominator = denominator; }

	//Metoda utilizata pentru compararea a doua fractii. Returneaza 0 daca fractiile sunt egale, 1, daca fractia ce apeleaza metoda este mai mare decat cea parametru, respectiv -1 in caz contrar.
	int compareTo(Fraction f2);


	//Supraincarcarea operatorului de atribuire permite copierea unei fractii in alta fractie
	Fraction operator = (Fraction const&  f2);

	//Supraincarcarea operatorului de egalare, verifica daca doua fractii sunt egale
	bool operator == (Fraction f2);

	//Supraincarcarea operatorului de comparare >, verifica daca fractia 1 mai mare decat fractia 2
	bool operator > (Fraction f2);

	//Supraincarcarea operatorului de egalitate >=, verifica daca o fractie este mai mare sau egala decat o alta.
	bool operator >= (Fraction f2);

	//Supraincarcarea operatorului de comparare <, verifica daca fractia 1 mai mai mica decat fractia 2
	bool operator < (Fraction f2);

	//Supraincarcarea operatorului de egalitate <=, verifica daca o fractie este mai mica sau egala decat o alta.
	bool operator <= (Fraction f2);

	//Evalueaza numarul rational sub forma de numar real
	double eval();

	

};

//Constructorul implicit
Fraction::Fraction():numerator(0),denominator(1){}

//Constructor inline de initializare a fractiei
Fraction::Fraction(int num,int den):numerator(num),denominator(den){}

//Constructor de copiere
Fraction::Fraction(Fraction const& f) {

	this->numerator = f.numerator;
	this->denominator = f.denominator;

}

//Metoda utilizata pentru compararea a doua fractii. Returneaza 0 daca fractiile sunt egale, 1, daca fractia ce apeleaza metoda este mai mare decat cea parametru, respectiv -1 in caz contrar.
int Fraction::compareTo(Fraction f2) {
	Fraction f1(*this);

	//Fractia 1 mai mare decat fractia 2
	if (f1.numerator * f2.denominator > f1.denominator * f2.numerator)
		return 1;

	//Fractia 1 mai mica decat 2
	if (f1.numerator * f2.denominator < f1.denominator * f2.numerator)
		return -1;

	//Fractia 1 egala cu fractia 2
	return 0;
}

//Compara 2 fractii si returneaza true daca fractia 1>fractia 2, respectiv 0 in caz contrar.
bool Fraction::operator > (Fraction f2){

	return (this->eval()>f2.eval());


}

bool Fraction:: operator == (Fraction f2) {

	return (this->eval()==f2.eval());

}

bool Fraction::operator >= (Fraction f2) {

	Fraction f1(*this);
	return (f1 > f2 || f1 == f2);

}

//Verifica daca fractia 1 > fractia 2
bool Fraction:: operator < (Fraction f2) {

	return (this->eval()<f2.eval());
}

//Verifica daca fractia 1 <= decat fractia 2
bool Fraction:: operator <= (Fraction f2) {

	Fraction f1(*this);
	return (f1 < f2 || f1 == f2);

}

//Copiere
Fraction Fraction:: operator = (Fraction const&f2) {

	this->numerator = f2.numerator;
	this->denominator = f2.denominator;
	return (* this);

}

//Evalueaza fractia sub forma de numar real
double Fraction::eval() {
	return this->numerator / (double)this->denominator;
}
