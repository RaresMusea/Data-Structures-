//Fisier Perm.h-> include clasa Permutare ce implementeaza conceptul de permutare, cat si posibilele operatii cu aceste elemente

#pragma once
//#include "Array.h"

class Permutare {
protected:
	//Vector de numere intregi in care vom retine elementele permutarii
	Array<unsigned int> data;

	//Gradul permutarii
	unsigned int grade;

public:
	//Constructori:
	//Constructorul implicit
	Permutare();

	//Constructorul inline de initializare
	Permutare(unsigned int const);

	//Constructor de copere 1 (permutarea curenta ia valoarea altei permutari)
	Permutare(Permutare const&);

	//Constructorul de copiere 2 (seteaza permutarea cu elementele date de array-ul pasat ca si parametru de intrare si cu gradul egal cu cel al variabilei grade.
	Permutare(Array<unsigned int> const&, unsigned int grade);

	
	//Setters (Mutators)
	//Metoda ce seteaza permutarea identica
	Permutare& setIdentic();

	//Metoda ce seteaza permutarea inversa
	Permutare& setReverse();

	//Metoda ce seteaza gradul permutarii
	void setGrade(unsigned int grade);

	//Supraincarcari de operatori:

	//Supraincarcarea operatorului de atribuire-confera copierea datelor in obiectul curent, din obiectul de tip Permutare, pasat drept parametru de intrare.
	Permutare& operator=(Permutare const&);

	
	//Supraincarcarea operatorului de indexare->o completare a supraincarcarii aceluiasi operator implementat si in clasa Array. Aceasta metoda va testa si limitele indicelul pasat ca si parametru de intrare.
	unsigned int operator[](unsigned int const& idx);

	//Supraincarcarea operatorului de inmultire-implementarea operatiei de compunere a permutarilor
	Permutare& operator*(Permutare const&);

	//Supraincarcarea operatorului de incremenetare->Obtinerea valorii permutarii succesoare
	Permutare& operator++ ();

	//Getters (Accesori):
	//Obtine inversa permutarii curente
	Permutare& getInverse() const;

	//Obtine gradul permutarii::
	unsigned int getGrade();

	//Metode de testare:
	//Metoda care verifica daca o permutare este sau nu valida
	bool isValid() const;

	//Metoda care testeaza daca o permutare este sau nu permutarea identica si returneaza true in caz afirmativ, respectiv false in caz contrar
	bool isIdentic() const;

	//Metoda care testeaza daca permutaea curenta este sau nu permutarea inversa si returneaza true in caz afirmativ, si respectiv false in caz contrar
	bool isReverse() const;

	//Metode de citire/afisare:
	//Afiseaza pe ecran permutarea
	void display();

	void create(int gr) {
		int count = gr;
		this->grade =gr;
		for (int i = 1; i <= count; i++) {
			do {
				cout << "data[" << i << "]= ";
				cin >> data[i];
			} while (i == data[i]);
			if (data[i]<1 || data[i]>count) {
				cout << "Valorea introdusa este invalida! \n";
				do {
					cout << "data[" << i << "]= ";
					cin >> data[i];
				} while (data[i] == i);
			}
		}
	}

	//Citeste permutarea de la tastatura
	void read(int deg);

	//Supraincarcarea operatorului de scriere in fluxul de iesire, utilizata pentru afisarea in consola a unei permutari
	friend ostream& operator<<(ostream& os, Permutare& perm) {
		perm.display();

		return os;
	}

	//Supraincarcarea operatorului de scriere in fluxul de intrare, utilizata pentru citirea de la tastatura a unei permutari
	friend istream& operator >> (istream& is, Permutare& perm) {
		
		Array<int> freq(perm.grade, 1);
		perm.data.setSize(perm.grade);
		perm.data.setBase(1);

		for (int i = 1; i <= perm.grade; i++)
		{
			unsigned int current;
			do {
				cout << "Elementul " << i;
				is >> current;
			} while (perm.data[i] > perm.grade && freq[i] != 1);
			perm.data[i] = current;
			freq[i] = 1;
		}
		return is;
	}

};

//Constructorii clasei:

//Constructor inline de initializare:Initializeaza vectorul data cu permutarea identica
Permutare::Permutare(unsigned int const nrgrade) :grade(nrgrade), data(nrgrade, 1) {
	for (int i = 1; i <= grade; i++)
		data[i] = i;
}

//Constructorul implicit
Permutare::Permutare() {

	grade = 0;
	data.setBase(1);
}

//Constructor de copiere 1
Permutare::Permutare(Permutare const& perm) {

	//Daca adresele de memorie difera, permutarii curente i se vor atribui valorile caracteristice permutarii perm, pasata ca si parametru de intrare
	if (this != &perm) {
		this->grade = perm.grade;
		this->data = perm.data;
	}
}

//Constructor de copiere 2 (permutarii curente i se vor atribui valorile pasate drept parametru de intrare al constructorului
Permutare::Permutare(Array<unsigned int> const& vect, unsigned int nrgrade) {

	this->grade = nrgrade;
	this->data = vect;

}

//Setters:
//Seteaza permutarea identica:
Permutare& Permutare::setIdentic() {

	//Permutarea identica presupune o functie cu puncte fixe de forma sigma(i)=i, oricare ar fi i<=grad,i>=1. 
	for (int i = 1; i <= grade; i++)
		this->data[i] = i;

	//La final, returnam valoarea obiectului curent.
	return *this;

}

//Seteaza permutarea inversa:
Permutare& Permutare::setReverse() {
	
	//Permutarea identica are valori de forma sigma(i)=grad-i+1, oricare ar fi i<=grad, i>=1.
	for (int i = 1; i <= grade; i++)
		this->data[i] = i;

	//Returnam valoarea obiectului curent
	return *this;
}

//Seteaza gradul permutarii
void Permutare::setGrade(unsigned int grade) {
	
	this->grade = grade;
}

//Supraincarcari de operatori
//Metoda ce utilizeaza supraincarcarea operatorului de atribuire in vederea asigurarii posibilitatii atribuirii unui obiect al clasei Permutare unui alt obiect apartinand aceleiasi clase.
Permutare& Permutare::operator=(Permutare const& perm) {
	
	//Atribuirea va fi posibila doar in situatia in care cele 2 obiecte au adrese de memorie distincte.
	if(this!=&perm){
		this->grade = perm.grade;
		this->data = perm.data;
	}

	//Returnam valoarea obiectului curent
	return *this;
}

//Supraincarcarea operatorului de inmultire-implementeaza operatia de compunere a permutarilor
Permutare& Permutare::operator* (Permutare const& perm){
	
	//x*y=x(y), unde x si y sunt 2 permutari
	for (int i = 1; i <= grade; i++)
		this->data[i] = perm.data[this->data[i]];

	//Returnam adresa obiectului curent
	return *this;

}

//Supraincarcarea operatorului de indexare-permite accesarea elementului cu indicele idx din permutarea curenta.
unsigned int Permutare::operator[](unsigned int const& idx) {

	if (idx >= 1 && idx <= grade)
		return this->data[idx];
	else
		cout << "Indexul depaseste gradul permutarii sau este o valoare negativa!\n";
}

//Supraincarcarea operatorului de incrementare->Permutarea succesoare
Permutare& Permutare::operator++() {

	unsigned int nrIndex = grade, nrAux, nrSec, nrTemp;

	while (data[nrIndex] < data[nrIndex - 1] && nrIndex>1)
		nrIndex--;

	//Daca exista succesor
	if (nrIndex > 1) {
		nrAux = grade;
		//Se va gasi cel mai mic element mai mare strict decat ultimul
		while (data[nrIndex - 1] > data[nrAux])
			nrAux--;

		//Interschimb elementele de pe pozitia nrIndex-1 si nrAux
		nrTemp = data[nrIndex - 1];
		data[nrIndex - 1] = data[nrAux];
		data[nrAux] = nrTemp;

		//Resortarea secventei terminale
		for(nrAux=nrIndex;nrAux<=grade-1;nrAux++)
			for(nrSec=nrAux+1;nrSec<=grade;nrSec++)
				if (data[nrAux] > data[nrSec]) {
					nrTemp = data[nrAux];
					data[nrAux] = data[nrSec];
					data[nrSec] = nrTemp;
				}
	}

	//La final, returnam valoarea obiectului curent
	return *this;
}

//Getters:
//Returneaza permutarea inversa a permutarii curente
Permutare& Permutare::getInverse() const {

	//Referinta la obiectul curent ce apeleaza metoda (copie a obiectului curent)
	Permutare* perm = new Permutare(*this);

	for (int idx = 1; idx <= grade; idx++)
		perm[data[idx]] = idx;

	//Returnam valoarea obiectului curent
	return *perm;
}

//Obtine gradul permutarii::
unsigned int Permutare:: getGrade() {
	return this->grade;
}



bool Permutare::isValid() const {

	//Definim un vector auxiliar
	Array<unsigned int> aux(grade, 1);

	//Populam vectorul cu valori de 0
	for (int i = 1; i < grade; i++)
		aux[i] = 0;

	for (int i = 1; i < grade; i++)
		//Permutare valida
		if (data[i] >= 1 && data[i] <= grade)
			aux[data[i]]++;
		//Permutare invalida
		else
			return false;

	//Permutarea invalida, deoarece fie a fost un duplicat, fie nu exista deloc.
	for (int i = 1; i < grade; i++)
		if (aux[i] != 1)
			return false;

	//Permutarea este una valida
	return true;
}

//Metoda care testeaza daca permutarea curenta este sau nu permutarea identica
bool Permutare:: isIdentic() const {

	for (int i = 1; i < grade; i++)
		if (data[i] != i)
			return false; //nu e permutarea identica
	
						  //e permutarea identica
	return true;
}

//Metoda care testeaza daca permutarea curenta este sau nu permutarea inversa
bool Permutare::isReverse() const {

	for (int i = 1; i < grade; i++)
		if (data[i]!= grade + 1 - i)
			return false; //nu e permutarea inversa

	//e permutarea inversa
	return true;

}

//Functie auxiliara utilizata de metoda display a clasei permutare in vederea afisarii elementelor unei permutari
void printValue(unsigned int& position) {
	cout << position << "\t";
}

//Metoda a clasei Permutare, ce utilizeaza functia mai sus declarata in vederea afisarii in consola a unei permutari
void Permutare:: display() {

	data.visit(printValue);
	cout << '\n';
}

//Metoda clasei Permutare, utilizata pentru a citi de la tastarura o permutare
void Permutare::read(int deg) {


	Array<int> freq(deg, 1);
	this->data.setSize(deg);
	this->setGrade(deg);
	this->data.setBase(1);

	for (int i = 1; i <= this->grade; i++)
		freq[i] = 0;

	for (int i = 1; i <= this->grade; i++)
	{
		unsigned int current;
		do {
			
			cout << "Elementul " << i<<": ";
			cin >> current;
			this->data[i] = current;
			freq[current]++;

		} while (this->data[i] > this->grade || freq[current]>1);
	}

}



