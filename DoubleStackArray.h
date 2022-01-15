//Fisier DoubleStackArray.h->Permite stocarea simultana a doua stive in acelasi vector suport
#pragma once


#include "Polinom.h"
#include "Exceptions.h"
#include <string>

//Clasa generica DoubleStack
template <class T>
class DoubleStack {

protected:
	//Membrii clasei:
	Array<T> arr;
	//Varful primei stive
	int topA;
	//Varful celeilalte stive
	int topB;
	//Dimensiunea totala a stivelor
	int sizeA, sizeB;
	//Numarul elementelor curente din fiecare stiva in parte
	int countA, countB;


public:
	//Constructorul de intitializare
	DoubleStack(int st1, int st2) :sizeA(st1), sizeB(st2), arr(st1 + st2) {
		//Varful primei stive
		topA = st1-1;
		
		//Varful celei de-a doua stive
		topB = st1;

		arr.setSize(st1+st2);

		//Numarul de elemente inserate in fiecare din cele 2 stive
		countA=0;
		countB=0;
	}


	//Constructor de copiere
	DoubleStack(DoubleStack<T> const& ds) :topA(ds.topA), topB(ds.topB), countA(ds.countA), countB(ds.countB), arr(ds.arr) {}

	//Constructor implicit
	DoubleStack() {}

	//Verifica daca stiva A e plina
	bool isAFull() {
		return (this->sizeA == this->countA);
	}

	//Verifica daca stiva A e goala
	bool isAEmpty() {
		return (this->countA == 0);
	}

	//Verifica daca stiva B e plina
	bool isBFull() {
		return (this->sizeB == this->countB);
	}

	//Verifica daca stiva A e B e goala
	bool isBEmpty() {
		return (this->countB == 0);
	}

	//Insereaza elementul el in stiva A
	void PushA(T const& el) {

		try {
			//Daca stiva A este plina, utilizatorul va fi intrebat daca doreste sa introduca elementul in cealalta stiva
			if (this->isAFull() && !this->isBFull())
			{
				cout << "Stiva A este plina. Doriti sa introduceti elementul in stiva B? (Y/N)";
				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y') {
					this->PushB(el);
					return;
				}
				//In cazul in care acesta refuza introducerea elementului in cea de-a doua stiva, un mesaj de eroare corespunzator se va afisa.
				else
					throw StackException();
			}

			//Daca cele 2 stive sunt pline, se va afisa un mesaj de eroare
			if (this->isAFull() && this->isBFull())
				throw StackException();

			//Se adauga elementul in stiva:

			if (countA != topA) {
				this->arr[countA++] = el;
				return;
			}

			if (countA == topA) {
				this->arr[topA] = el;
				countA++;
				return;
			}

			//Tratarea posibilelor exceptii care pot aparea
			throw StackException();
		}
		catch (StackException& se) {
			se.handle("Eroare!\nNu s-a putut insera elementul " + to_string(el) + "in niciuna din cele 2 stive!\nVerificati dimensiunile stivelor!\n");
		}
	}

	//Elimina un element din stiva A:
	void PopA() {

		//Daca stiva A este goala, ,,arunca'' o exceptie
		try {
			if (this->isAEmpty())
				throw StackException();

			//Actualizeaza variabilele membru (scade pozitia varfului, numarul de elemente introduse si dimensiunea efectiva a stivei A)
			topA--;
			countA--;
			sizeA--;
		}
		//Tratam exceptia
		catch (StackException& se) {
			se.handle("Eroare!\nStiva A este goala!");
		}


	}

	//Adauga un element in stiva B
	void PushB(T const& el) {
		try {
			//Daca stiva B este plina, iar in stiva A inca mai pot fi adaugate elemente, utilizatorul este intrebat daca doreste sa insereze elementul in cealalta stiva.
			if (this->isBFull() && !this->isAFull())
			{
				cout << "Stiva B este plina. Doriti sa introduceti elementul in stiva A? (Y/N)";
				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y') {
					this->PushA(el);
					return;
				}
				//Daca raspunsul este unul negativ, un mesaj de eroare va fi afisat.
				else
					throw StackException();
			}

			//Daca ambele stive sunt goale, un mesaj de eroare va fi afisat.
			if (this->isAFull() && this->isBFull())
				throw StackException();

			//Adaugarea propriu-zisa a elementului
			if (countB != arr.getSize() - topB+1) {
				this->arr[this->arr.getSize()-1-countB] = el;
				countB++;
				return;
			}

			if (countB == topB) {
				this->arr[topB] = el;
				countB++;
				return;
			}

			//Tratarea posibilelor exceptii care mai pot aparea
			throw StackException();
		}
		
		//Tratare exceptii
		catch (StackException& se) {
			se.handle("Eroare!\nNu s-a putut insera elementul " + to_string(el) + "in niciuna din cele 2 stive!\nVerificati dimensiunile stivelor!\n");

		}
	}

	//Elimina elementul din varful stivei B
	void PopB() {
		//Daca stiva B este goala, ,,arunca'' o exceptie
		try {
			if (this->isBEmpty())
				throw StackException();

			//Actualizam variabilele membru
			topB++;
			countB++;
			sizeB--;
		}
		//Tratam exceptia
		catch (StackException& se) {
			se.handle("Eroare!\nStiva B este goala!");
		}


	}

	//Supraincarcarea operatorului de scriere in fluxul de intrare, permite citirea unei stive duble de la tastatura.
	friend istream& operator >> (istream& istr, DoubleStack<T>& ds) {

		cout << "Cate elemente are prima stiva? ";
		istr >> ds.sizeA;

		cout << "Cate elemente are cea de-a doua stiva? ";
		istr >> ds.sizeB;

		ds = DoubleStack(ds.sizeA, ds.sizeB);

		for (int i = 0; i < ds.arr.getSize(); i++)
		{
			cout << "In care stiva doriti sa introduceti elementul " << i + 1 << "? (A/B)";
			char choice;
			istr >> choice;
			cout << "Care este valoarea elementului ?";
			T current;
			istr >> current;
			if (choice == 'A' || choice == 'a')
				ds.PushA(current);
			else
				ds.PushB(current);

		}

		return istr;

	}
	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite citirea unei stive duble de la tastatura.
	friend ostream& operator << (ostream& ostr, DoubleStack<T>& ds) {
		ostr << "\n";

		//Stiva A:
		ostr << "Stiva A:\n";
		for (int i =ds.topA; i>=0; i--)
			ostr << ds.arr[i] << '\n';

		ostr << '\n';

		//Stiva B:
		ostr << "Stiva B:\n";

		for (int i = ds.topB; i <= ds.arr.getSize() - 1; i++)
			ostr << ds.arr[i] << "\n";

		ostr << "\n";


		cout << "Elementul din varful stivei A: " << ds.arr[ds.topA] << '\n' << "Elementul din varful stivei B: " << ds.arr[ds.topB] << "\n";

		return ostr;

	}

};
