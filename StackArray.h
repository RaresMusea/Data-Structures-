//Fisier header StackArray.h->Implementeaza clasa StackArray, care este o implementare a unei stive sub forma unui tabou unidimensional (stiva statica)

#pragma once
#include"Stack.h" //Folosim interfata Stack
//#include "Array.h" //Vector unidimensional
#include "Exceptions.h" //Fisier in care am definit numeroase exceptii ce vor fi tratate in cadrul clasei StackArray
#include "Polinom.h" //foloseste clasa Array si functia erase, care elimina un element dintr-o instanta a clasei Array

//Clasa generica StackArray, foloseste interfata Stack
template <class T>
class StackArray: public Stack<T>{

public:
	//Variabile membru:
	//Vectorul suport
	Array<T> arr;

public:

	//Constructor implicit
	StackArray() {
		this->count = 0;
	}

	//Constructorul de initializare al stivei->Initializeaza vectorul suport al stivei cu un numar de Size elemente.
	StackArray (unsigned int Size) :arr(Size){
		this->count = 0;
		this->arr.setSize(Size);
	}

	//Constructorul de copiere->Copiaza array-ul suport al stivei-parametru in stiva curenta.
	StackArray(StackArray<T> const& s) :arr(s.arr){
		this->count = s.getCount();
		this->arr.setSize(s.arr.getSize());
	}

	//Destructor
	~StackArray(){}

	//Metode ex.1

	int readFromTop();
	int readFromBase();
	void deleteFromStack(T value);

	//Metoda care verifica daca valorile dintr-o stiva sunt sau nu sortate
	bool isSorted();

	//Iterclaseaza 2 stive sortate
	StackArray<T> merge(StackArray<T> &s2);

	//Metoda care verifica daca un anume element exista in stiva
	bool contains(T val);

	//Returneaza elementul din varful stivei
	T& getTop(){
		
		//Se incearca returnarea elementlului din varful stivei
		try {
			//Daca stiva este goala, ''arunca'' o exceptie
			if (this->count == 0)
				throw StackException();
			return this->arr[this->count - 1];
		}
		//Tratarea exceptiei
		catch (StackException& se) {
			se.handle("Eroare!\nStiva este goala!");
		}
	}

	//Metoda care retuneaza elementul de la baza stivei:
	T& getBase();


	//Elimina un element din varful stivei
	void pop() {

		//Daca stiva este goala, ,,arunca'' o exceptie
		try {
			if (this->count == 0)
				throw StackException();
			this->count--;
		}
		//Tratam exceptia
		catch (StackException& se) {
			se.handle("Eroare!\nStiva este goala!");
		}
	}

	//Adauga un element in stiva
	void push(T const& t) {

		//Se incearca adaugarea elementului
		try {
			//In situatia in care stiva este plina, se va lansa o exceptie
			if (this->count == this->arr.getSize())
				throw StackException();
			this->arr[this->count++] = t;
		}
		//Se trateaza exceptia
		catch(StackException& se) {
			se.handle("Eroare!\nNu se mai pot adauga elemente in stiva, intrucat aceasta este plina!\n");
		}	
	}

	//Verifica daca stiva este goala si returneaza true (in caz afirmativ), respectiv false (in caz contrar)
	bool isEmpty() const {
		return (this->count == 0);
	}

	//Verifica daca stiva este plina si returneaza true (in caz afirmativ), respectiv false (in caz contrar)
	bool isFull() const {
		return (this->count == this->arr.getSize());
	}

	//Returneaza dimensiunea efectiva a stivei.
	unsigned int getCount() const {
		return this->count;
	}

	//Supraincarcarea operatorului de scriere in fluxul de intrare, permite citirea de la tastatura a unei stive.
	friend istream& operator >> (istream& istr, StackArray<T>& st) {

		//Citim stiva
		int counter;
		cout << "Cate elemente are stiva? "; istr >> counter;
		st = StackArray<T>(st.count);

		for (int i = 0; i < st.count; i++)
		{
			T el;
			cout << "Elementul " << i + 1 << ": "; istr >> el;
			st.arr[i] = el;
		}

		return istr;
	}

	//Supraincarcarea operatorului de scriere in fluxul de iesire, permite afisarea pe ecran a unei stive
	friend ostream& operator << (ostream& ostr, StackArray<T> &st) {

		ostr << '\n';

		//Afisam stiva
		for (int i = st.arr.getSize() - 1; i >= 0; i--)
			ostr << st.arr[i]<<'\n';
	
		ostr << '\n';
		return ostr;

	}

	//Inverseaza valorile din stiva
	void reverseStack();


};


//Returneaza elementul de la baza stivei
template <class T>
T& StackArray<T>::getBase() {

	//Incearca sa obtina elementul de la baza stvei
	try {
		//Daca stiva este goala, atunci, afiseaza mesaj de eroare (trateaza exceptia)
		if (this->isEmpty())
			throw StackException();
		//returneaza elementul de la baza stivei, in situatia in care stiva nu este goala
		return this->arr[0];
	}
	catch (StackException& se) {
		se.handle("Eroare!\nStiva este goala!");
	}

}

//Metode ex 1
//Subpunctul a)
//Metoda care citeste un element din varful stivei, fara a - l sterge. Daca s este vida, x = INT_MAX;
template <class T>
int StackArray<T>::readFromTop() {

	//Initializam variabila x
	int x = 1;
	
	//Daca stiva curenta este, vida, x=INT_MAX
	if (this->isEmpty())
		x = INT_MAX;
	else
		//Afiseaza elementul din varful stivei
		cout << "Elementul din varful stivei: " << this->getTop() << '\n';
	return x;

}

//Subpunctul b)
//Metoda care citeste in x elementul de la baza stivei (x = INT_MAX daca stiva este goala) si lasa stiva neschimbata;
template <class T>
int StackArray<T>::readFromBase() {

	//Situatia in care stiva este goala
	int x =INT_MAX;

	//Daca stiva nu este goala, retinem in x elementul de la baza stivei
	if (!this->isEmpty()) {
		x = this->getBase();
	}

	//Returnam x
	return x;

}


//Subpunctul c)
//sterge toate elementele egale cu x din stiva, lasand celelalte elemente nealterate.

template<class T>
void StackArray<T>::deleteFromStack(T value) {
	
	//Cautam pozitia valorii value
	int p = this->arr.contains(value);
	//Cat timp valoarea de eliminat se regaseste in array
	while (p >= 0)
	{
		//O eliminam
		erase(this->arr, p);
		//Actualizam dimensiunea stivei
		this->count = this->arr.getSize();
		//Reinitializam urmatoarea pozitie pe care se gaseste valoarea value:
		p = this->arr.contains(value);
	}
}

//Metoda care verifica daca un anume element exista in stiva
template <class T>
bool StackArray<T>::contains(T val) {

	//Apelam metoda clasei array contains(), care utilizeaza cautarea binara pentru a vedea daca o valoare se gaseste sau nu in array
	int res = this->arr.contains(val);

	//Daca rezultatul returnat de metoda contains este unul negativ, inseamna ca valoarea nu exista in stiva
	if (res < 0)
		return false;
	
	//Valoarea exista in stiva
	return true;
}

//Verifica daca vectorul suport al unei stive statice este sau nu sortat.
template <class T>
bool StackArray<T>::isSorted() {

	for (int i = 0; i < this->arr.getSize() - 1; i++) {
		if (this->arr[i] > this->arr[i + 1])
			return false;
	}

	return true;

}
//
////Interclaseaza doua stive
//template <class T>
//StackArray<T> StackArray<T>::merge(StackArray<T> &s2)
//{
//	StackArray<T> res(this->arr.getSize() + s2.arr.getSize());
//	try
//	{
//		if (!this->isSorted() && !s2.isSorted())
//		{
//			throw StackException();
//			return res;
//		}
//
//
//		while ((!this->isEmpty()) && (!s2.isEmpty()))
//		{
//			count++;
//			if (this->getTop() < s2.getTop())
//			{
//				res.push(s2.getTop());
//				s2.pop();
//			}
//			else
//			{
//				res.push(this->getTop());
//				this->pop();
//			}
//		}
//
//
//		if (!this->isEmpty())
//		{
//			while (!this->isEmpty())
//			{
//				res.push(this->getTop());
//				this->pop();
//			}
//		}
//		if (!s2.isEmpty())
//		{
//			while (!s2.isEmpty())
//			{
//				res.push(s2.getTop());
//				s2.pop();
//			}
//		}
//
//		//res.reverseStack();
//
//		return res;
//	}
//	catch (StackException& se)
//	{
//		se.handle("EROARE!\n Nu se poate realiza interclasarea, intrucat stivele nu sunt sortate!");
//	}
//}

//Inverseaza valorile din stiva
template<class T>
void StackArray<T>::reverseStack()
{
	StackArray<T> temp(this->arr.getSize());
	while(!this->isEmpty())
	{
		temp.push(this->getTop());
		this->pop();
	}

	(*this) = temp;
}




