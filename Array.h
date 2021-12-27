//Header File Array.h-> definirea unei clase pentru stocarea unui tablou unidimensional, cat si a operatiilor cu acestea
#include<iostream>

using namespace std;

//Clasa generica
template <class T>

class Array {
protected:
	//Variabile membru ale clasei
	T* data;
	unsigned int base;
	unsigned int size;

public:
	//Constructori:
	
	//Constructor implicit
	Array();
	
	//Constructor de initializare
	Array(unsigned int Size, unsigned int Base = 0);

	//Constructor de copiere
	Array(Array const& arr);

	//Destructor
	~Array();


	//Prototipuri metode:
	//Supraincarcare operator de atribuire-permite atribuirea unui obiect de tip Array unui alt obiect cu acelasi tip de date
	Array& operator=(Array const& array);

	//Supraincarcare operator de indexare-Permite accesarea elementului de pe pozitia position, fara modificarea valorii
	T const& operator[] (unsigned int position)const;

	//A doua supraincarcare a operatorului de indexare-Permite accesarea elementului de pe pozitia position, cu posibilitatea modificarii valorii stocate in elementul de pe pozitia respectiva
	T& operator[] (unsigned int position);

	//Getter pentru elementele din array
	T const* getData() const;

	//Getter pentru baza array-ului (indicele de la care se incepe numerotarea elementelor)
	unsigned int getBase() const;

	//Getter pentru obtinerea lungimii efective a array-ului
	unsigned int getSize() const;

	//Setter pentru baza array-ului (indicele de la care se va incepe numerotarea elementelor)
	void setBase(unsigned int base);

	//Setter pentru stabilirea dimensiunii efective a array-ului
	void setSize(unsigned int size);

	//Metoda de tip iterator, utilizata pentru parcurgerea array-ului
	void visit(void (*fun)(T&))
	
};

//Definirea constructorilor, a destructorilor si a metodelor:
//1. Constructori:
//Constructorul implicit:Constructor inline:
template <class T>
Array<T>::Array() :data(new T[0]), base(0), size(0);

//Constructorul de initializare (constructor inline):
template <class T>
Array<T>::Array(unsigned int Size, unsigned int Base) :data(new T[Size]), base(Base), size(Size);

//Constructorul de copiere-Construieste o copie a obiectului pasat ca si parametru in obiectul curent:
template <class T>
Array<T>::Array(Array<T>const& arr) {

	//Daca adresele de memorie difera, se va sterge continutul obiectului curent si se va copia in acesta, datele din obiectul pasat ca si parametru constructorului.
	if (this != &array) {

		delete this->[]data;
		this->size = arr.size;
		this->base = arr.base;
		this->data = new T[size];

		for (int i = 0; i < this->size; i++)
			this->data[i] = arr.data[i];
	
	}
}

//2.Destructori:
//Destructorul clasei Array dealoca memoria alocata pentru pointer-ul data (doar in situatia in care aceasta a fost alocata).
template <class T>
Array<T>::~Array() {
	
	//Daca pointer-ul pointeaza catre o adresa, se va elibera memoria alocata.
	if (data)
		delete[]data;
}

//3.Metode propriu-zise:
//Getters:
//a. getData()-> accesor ce returneaza membrul data al clasei Array
template<class T>
T const* Array<T>::getData() const{

	return this->data;

}

//b. getBase()->accesor ce returneaza membrul base al clasei Array (index-ul de start al array-ului)
template<class T>
unsigned int Array<T>::getBase() const {

	return this->base;
}

//c. getSize()->accesor ce returneaza membrul size al clasei Array (dimensiunea efectiva a array-ului)
template <class T>
unsigned int Array<T>::getSize() const {

	return this->size;
}

//Setters
//a. setSize()->mutator ce seteaza valoarea membrului size al clasei Array (dimensiunea efectiva a array-ului)
template<class T>
void Array<T>::setSize(unsigned int size) {

	this->size = size;
}

//b. setBase()->mutator ce seteaza valoarea membrului base al clasei Array (index-ul de start al array-ului)
template <class T>
void Array<T>::setBase(unsigned int base) {

	this->base = base;
}

//Functia ce va fi apelata de catre functia de tip iterator (visit)
template<class T>
void fun(T& val) {
	cout << val << " ";
}

//Metoda de tip iterator (visit):parcurge toate elementele array-ului si le afiseaza, prin apel direct la functia fun(), definita anterior.
template<class T>
void Array<T>::visit(void(*fun)(T&)) {

	for (int i = 0; i < size; i++)
		fun(data[i]);
}

//Supraincarcari de operatori
//Supraincarcarea operatorului de atribuire, confera o functionalitate asemanatoare constructorului de copiere
template <class T>
Array<T>& Array<T>::operator= (Array<T> const& array) {

	//Daca adresele de memorie difera, se va trece la copierea propriu-zisa:
	if (this != &array) {
		delete []this->data;
		this->size = array.size;
		this->base = array.base;
		this->data = new T[this->size];

		for (int i = 0; i < size; i++)
			this->data[i] = array.data[i];
	}

	//Returnam valoarea obiectului curent
	return *this;
}

//Supraincarcare operator de indexare (r-value):se va folosi cand valoarea indexata este o valoarea de dreapta intr-o expresie (valoarea va trebui sa ramana constanta)
template <class T>
T const& Array<T>::operator[](unsigned int position) const{

	unsigned int const offset = position - base;

	if (offset > size) {
		cout << "Pozitie invalida!\n";
		return;
	}
	return data[offest];
}

//Supraincarcarea operatorului de indexare (l-value). Permite accesarea membrului data, cu indicele position, in momentul in care acesta apare in stanga expresiei/atribuirii.
template <class T>
T& Array<T>::operator[](unsigned int position) {

	unsigned int const offset = position - base;

	if (offset > size) {
		cout << "Pozitie invalida!\n";
		return;
	}
	return data[offset];
}




