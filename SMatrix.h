#pragma once
//SMatrix.h->Header file ce contine clasa SMatrix, ce implementeaza conceptul de matrice rara, alaturi de diferite operatii ce se pot realiza cu ajutorul acesteia.

#include"SortArray.h"
#include"Entry.h"
#include <exception>


class MatrixSizeException :public exception
{
public:
	void handle() const throw() {
		cout << "Ati introdus o dimensiune a matricei mai mica decat cea a bandei!\nNu se poate construi matricea banda!\n\n";
	}
};




//Clasa generica SMatrix, ce foloseste atat clasa Entry, cat si clasa SortArray
template <class T>
class SMatrix {
protected:
	//Membrii ai clasei:
	//numarul de linii al matricei rare
	unsigned int rows; 
	//numarul de coloane al matricei rare
	unsigned int cols;
	//numarul de valori nenule al matricei rare
	unsigned int count;
	//Valorile vor fi stocate intr-o lista ordonata, sub forma tripletului de forma (linie, coloana, valoare), definit pe baza clasei Entry.
	SortArray<Entry<T>> data;

public:
	//Constructori:
	//Constructor inline de initializare
	SMatrix(unsigned int r, unsigned int c) :rows(r), cols(c), count(0){}

	//Constructor implicit
	SMatrix(){}
	//Metode:
	//Metoda care verifica daca matricea rara contine doar elemente nule (elemente de 0).
	bool isNull() {
		return (count == (0));
	}

	//Prototipuri:
	//Getter (Accesor) pentru lista ordonata de intrari in matricea rara.
	SortArray<Entry<T>>& getData();
	
	//Getter ce retuneaza numarul de linii ale matricei rare
	unsigned int getRows();
	
	//Getter ce returneaza numarul de coloane ale matricei rare
	unsigned int getCols();

	//Getter ce returneaza numarul de elemente nenule ale matricei rare
	unsigned int getCount();

	//Setter ce seteaza numarul de linii din matricea rara
	void setRows(unsigned int rows);

	//Setter ce seteaza numarul de coloane din matricea rara
	void setCols(unsigned int cols);
	
	//Setter ce seteaza numarul de valori nenule din matricea rara
	void setCount(unsigned int count);

	//Metoda ce construieste o matrice rara de tip ,,banda", cu 3 elemente pe banda
	SMatrix<T>& band3Matrix();

	//Metoda ce construieste o matrice rara de tip "banda", cu b elemente pe banda.
	SMatrix<T>& bandMatrix();

	//Functie utilizata pentru afisarea unei matrice banda, pornind de la conceptul de matrice rara.
	void printBandMatrix();

	//Metoda ce permite adaugarea unei noi intrari in matricea rara
	SMatrix<T>& addEntry(Entry<T> const& e) {
		if ((e.row < 0) || (e.row > rows) || (e.col < 0) || (e.col > cols)) {
			cout << "Eroare";
			return *this;
		}
		int pos = this->data.findValue(e);
		if (pos < 0) {
			this->data = this->data + e;
			count++;
		}
		else {
			Entry<T>& curent = data[pos];
			T sum = curent.val + e.val;
			if (sum == 0.0) {
				data = data - curent;
				count--;
			}
			else {
				curent.val = sum;
			}
		}
		return *this;
	}

	//Metoda ce permite elimonarea unei intrari din matricea rara
	SMatrix<T>& subtractEntry(Entry<T>& e);

	//Metoda ce permite inseraea unei noi valori in matricea rara
	SMatrix<T>& addValue(unsigned int r, unsigned int c, T const& e);

	//Metoda responsabila de eliminarea unei valori din matricea rara
	SMatrix<T>& removeValue(unsigned int r, unsigned int c, T const& e);

	//Metoda ce creaza o matrice rara, populand-o cu elemente nenule:
	void create();

	//Metoda responsabila de eliminare tuturor valorilor din matricea rara.
	SMatrix<T>& reset();

	//Metoda ce afiseaza pe ecran continutul unei matrice rare (doar valorile nenule)
	void display();

	//Metoda ce calculeaza transpusa unei matrice rare
	SMatrix<T>& transp(SMatrix<T> const& A);

	//Supraincarcari de operatori
	//Metoda ce utilizeaza supraincarcarea operatorului de atribuire in vederea copierii in obiectul curent a matricii rare pasate ca si parametru de intrare.
	SMatrix<T>& operator = (SMatrix<T> const& p);

	//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea adaugarii unei noi intrari in matricea rara
	SMatrix<T>& operator + (Entry<T> const& t);

	//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea calculului sumei a doua matrice rare.
	SMatrix<T>& operator + (SMatrix<T> const& m);
	
	//Metoda ce utilizeaza supraincarcarea operatorului de scadere pentru eliminarea unei intrari din matricea rara.
	SMatrix<T>& operator - (Entry<T> const& t);

	//Metoda ce utilizeaza supraincarcarea operatorului de scadere pentru a calcula diferenta a doua matrice rare.
	SMatrix<T>& operator - (SMatrix<T> const& m);

	//Metoda ce utilizeaza supraincarcarea operatorului de inmultire pentru a permite calculul produsului dintre o matrice rara si o constanta.
	SMatrix<T>& operator * (T const& t);

	//Metode prieten
	
	//Metoda prieten de citire a matricei la un flux de intrare (istream) (echivalenta cu metoda create)
	friend istream& operator>> (istream& i, SMatrix<T>& m) {
		
		//Variabile pentru numarul de linii, coloane, respectiv elemente nenule din matricea rara ce va fi citita.
		unsigned int rows, columns, count;

		//Citire campuri
		cout << "Cate linii are matricea? ";
		cin >> rows;
		m.setRows(rows);

		cout << "Cate coloane are matricea? ";
		cin >>columns;
		m.setCols(columns);

		//Retinem numarul elementelor nenule ce se vor regasi in matrice
		unsigned int counter;
		cout << "Cate elemente nenule se regasesc in matricea rara? ";
		cin >> count;

		//Inserare elemente
		int r, c, v;
		for (int i = 0; i < count; i++)
		{
			cout << "Elementul " << i + 1 << '\n';
			cout << "Linia: "; cin >> r;
			cout << "Coloana: "; cin >> c;
			cout << "Valoarea elementului: "; cin >> v;
			m.addValue(r, c, v);
		}
		return i;
	}

	//Metoda prieten de afisare a matricei la un flux de iesire (ostream)
	friend ostream& operator<< (ostream& o, SMatrix<T>& p) {
		int k = 0;
		for (int i = 0; i < p.rows; i++) {
			for (int j = 0; j < p.cols; j++) {
				if (k < p.data.getSize() && p.data[k].row == i && p.data[k].col == j) {
					cout << p.data[k++].val << "\t";
				}
				else
					cout << 0 << "\t";
			}
			cout << "\n";
		}

		return o;
	}

	//Destructori:
	//Destructor inline
	~SMatrix(){
		rows = 0;
		cols = 0;
		count = 0;
	}

};

//Getters:
//Metoda-accesor (getter) ce permite accesul la lista ordonata ce descrie structura matricei rare SMatrix
template <class T>
SortArray<Entry<T>>& SMatrix<T>::getData() {
	return data;
}

//Getter ce retunraza numarul de linii ale matricei rare
template <class T>
unsigned int SMatrix<T>:: getRows() {
	return rows;
}

//Getter ce retunreaza numarul de coloane ale matricei rare
template <class T>
unsigned int SMatrix<T>::getCols() {
	return cols;
}

//Getter ce returneaza numarul elementelor nenule din matricea rara.
template <class T>
unsigned int SMatrix<T>::getCount() {
	return count;
}

//Setters:

//Setter pentru stabilirea numarului de linii din matricea rara
template <class T>
void SMatrix<T>::setRows(unsigned int rows) {
	this->rows = rows;
}

//Setter pentru stabilirea numarului de coloane din matricea rara
template <class T>
void SMatrix<T>::setCols(unsigned int cols) {
	this->cols = cols;
}

//Setter pentru stabilirea numarului de valori nenule din matricea rara
template <class T>
void SMatrix<T>::setCount(unsigned int count) {
	this->count = count;
}

//Metode (definitii):

//Metoda ce permite eliminarea unui triplet de tipul (linie, coloana, valoare) din matricea rara.
template <class T>
SMatrix<T>& SMatrix<T>::subtractEntry(Entry<T>& e) {
	e.val = -e.val;
	return addEntry(e);
}

//Metoda care permite adaugarea unei noi valori in matricea rara.
template<class T>
SMatrix<T>& SMatrix<T>::addValue(unsigned int r, unsigned int c, T const& e) {

	//Construim un nou entry si il adaugam in matricea rara, prin apel la functiile declarate anterior.
	Entry<T> t(r, c, e);
	return addEntry(t);

}

//Metoda ce permite eliminarea unei valori din matricea rara
template <class T>
SMatrix<T>& SMatrix<T>::removeValue(unsigned int r, unsigned int c, T const& e) {
	
	//Inversam valoarea din entry, dupa care o adaugam in matrice, prin apel la metodele anterior definite.
	Entry<T>t(r, c, -e);
	return addEntry(t);
}

//Metoda responsabila de eliminarea tuturor valorilor din matricea rara.
template <class T>
SMatrix<T>& SMatrix<T>::reset() {
	
	data.setSize(0);
	count = 0;
}

//Supraincarcarea operatorului de atribuire:copierea valorii din matricea-parametru in obiectul curent.
template <class T>
SMatrix<T>& SMatrix<T>:: operator = (SMatrix<T> const& p) {
	
	//Copiere campuri
	data = p.data;
	rows = p.rows;
	cols = p.cols;
	count = p.count;

	//Returneaza valoarea obiectului curent
	return *this;
}

//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea adaugarii unei noi intrari in matricea rara
template<class T>
SMatrix<T>& SMatrix<T>:: operator + (Entry<T> const& t) {
	return addEntry(t);
}

//Metoda ce utilizeaza supraincarcarea operatorului de insumare in vederea calculului sumei a doua matrice rare.
template <class T>
SMatrix<T>& SMatrix<T>:: operator+(SMatrix<T> const& m) {

	//Situatia in care cele 2 matrice sunt incompatibile
	if ((m.rows != rows) || (m.cols != cols))
	{
		cout << "Nu se pot aduna 2 matrice de dimensiuni diferite!\n";
		return *this;
	}

	//Matricele sunt compatibile
	for (int i = 0; i < m.data.getSize(); i++)
		addEntry(m.data[i]);

	//Returnam valoarea obiectului curent
	return *this;
}

template <class T>
//Metoda ce utilizeaza supraincarcarea operatorului de scadere pentru eliminarea unei intrari din matricea rara.
SMatrix<T>& SMatrix<T>:: operator - (Entry<T> const& t) {
	return subtractEntry(t);
}

template <class T>
//Metoda ce utilizeaza supraincarcarea operatorului de scadere pentru a calcula diferenta a doua matrice rare.
SMatrix<T>& SMatrix<T>:: operator - (SMatrix<T> const& m) {
	
	//Situatia in care matricele sunt incompatibile
	if ((m.rows != rows) || (m.cols != cols)) {
		cout << "Nu se pot aduna 2 matrice de dimensiuni diferite!\n";
		return *this;

	}

	//Cazul contar:Matricele sunt compatibile
	for (int i = 0; i < m.data.getSize(); i++)
		subtractEntry(m.data[i]);

	//Returnam valoarea obiectului curent
	return *this;
}

//Metoda ce supraincarca operatorul de inmultire in vederea calculului produsului dintre o matrice rara si o constanta
template <class T>
SMatrix<T>& SMatrix<T>:: operator * (T const& t) {
	
	//Inmultirea cu 0 duce la resetarea matricei rare
	if (t == 0)
		this->reset();
	//Inmultirea propriu-zisa:
	else
		for (int i = 0; i < data.getSize(); i++)
			this->data[i].val = this->data[i].val * t;
	return *this;
}

//Metoda ce afiseaza pe ecran continutul unei matrice rare (doar valorile nenule)
template <class T>
void SMatrix<T>:: display() {
	
	//Construim o lista sortata de intrari, in care vom copia valorile nenule din matricea rara, alaturi de coordonatele acestora (linii,coloane). 
	SortArray<Entry<T>> a;

	//Copiere
	a = this->getData();

	//Afisare:
	for (int i = 0; i < a.getSize(); i++) {
		if (i != a.getSize() - 1)
			cout << "( " << a[i].row << "," << a[i].col << "," << a[i].val << " ) ,  ";
		else
			cout << "( " << a[i].row << "," << a[i].col << "," << a[i].val << " )";
	}
}

//Metoda responsabila de crearea unei matrice rare si popularea acesteia cu elemente nenule:
template <class T>
void SMatrix<T>::create() {
	
	//Citire campuri
	cout << "Cate linii are matricea? ";
	cin >> this->rows;

	cout << "Cate coloane are matricea? ";
	cin >> this->cols;
	
	//Retinem numarul elementelor nenule ce se vor regasi in matrice
	unsigned int count;
	cout << "Cate elemente nenule se regasesc in matricea rara? ";
	cin >> count;

	//Inserare elemente
	int r, c, v;
	for (int i = 0; i<count; i++)
	{
		cout << "Elementul " << i + 1<<'\n';
		cout << "Linia: "; cin >> r;
		cout << "Coloana: "; cin >> c;
		cout << "Valoarea elementului: "; cin >> v;
		this->addValue(r, c, v);
	}

}

//Metoda ce calculeaza transpusa unei matrice rare
template<class T>
SMatrix<T>& SMatrix<T>::transp(SMatrix<T> const& A) {

	//liniile vor deveni coloane, iar coloanele vor deveni linii
	for (int i = 0; i < A.count; i++) {
		this->data[i].row = A.data[i].col;
		this->data[i].col= A.data[i].row;
	}

	//Returnam valoarea obiectului curent
	return *this;
}


//Metoda a clasei SMatrix , care genereaza o matrice banda pornind de la input-ul utilizatorului (dimensiunea benzii b=3)
template <class T>
SMatrix<T>& SMatrix<T>::band3Matrix() {

	SMatrix<int> construct = *this;
	int band = 3;
	unsigned int r = 0, c = 0;
	do {
		try {
			cout << "Introduceti numarul de coloane: ";
			cin >> c;

			cout << "Introduceti numarul de linii: ";
			cin >> r;

			//In situatia in care input-ul introdus de utilizator nu este unul valid, se va "arunca" o exceptie
			if (r < band || c<band || r>c || (r == band && c == band))
				throw MatrixSizeException();
		}
		catch (MatrixSizeException& mex) {
			mex.handle();
			exit(0);
		}
	} while (r < band || c < band);

	//Configuram matricea rezultanta
	construct.setCols(c);
	construct.setRows(r);

	//Construim prima linie
	for (int i = 0; i < band - 1; i++)
		construct.addValue(0, i, 1);

	//Construim ultima linie
	for (int i = c - band + 1; i < c; i++)
		construct.addValue(r - 1, i, 1);

	//Construim celelalte linii
	int idx = 0, spacing = 0;
	for (int i = 1; i < r - 1; i++) {
		while (idx < band) {
			construct.addValue(i, idx + spacing, 1);
			idx++;
		}
		idx = 0;
		spacing++;
	}

	//Copiem in obiectul curent rezultatul si il returnam
	*this = construct;

	return *this;

}


template <class T>
void SMatrix<T>::printBandMatrix() {

	int k = 0;
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			if (k < this->data.getSize() && this->data[k].row == i && this->data[k].col == j) {
				cout << "X" << "\t";
				k++;
			}
			else
				cout << 0 << "\t";
		}
		cout << "\n";
	}
}

//Metoda a clasei SMatrix ce construieste o matrice banda (banda de dimensiuni variabile)
template <class T>
SMatrix<T>& SMatrix<T>::bandMatrix() {

	SMatrix<int> construct = *this;
	//In cazul matricei banda cu b elemente pe banda, variabila band va urma a fi citita de la tastatura.
	int r, c, band, size;

	//Citirea variabilelor necesare 
	//Dimensiunea benzii
	cout << "Dimesniunea benzii: ";
	cin >> band;
	do {
		try {

			//Numarul de coloane
			cout << "Introduceti numarul de coloane ale matricei:";
			cin >> c;

			//Cazul in care banda este mai mare strict decat 3 impune conditia ca numarul de linii sa fie mai mic decat cel de coloane si cel putin egal cu dimensiunea benzii
			if (band > 3) {
				cout << "Introduceti numarul de linii ale matricei: (Pentru numarul de coloane introduse anterior, anume " << c << " se recomanda un numar mai mic decat acesta, astfel incat matricea sa poata fi afisata corespunzator) :";
			}

			//Cazul tratat partial in functia precedenta (banda<=3)
			else {
				cout << "Introduceti numarul de linii ale matricei: ";
			}

			//Citim numarul de linii
			cin >> r;

			//Tratam posibilele exceptii ce pot aparea

			if (band > 3)
				if (c < band || r>c || (r == band && c == band))
					throw MatrixSizeException();
				else {
					if (c < band || r>c)
						throw MatrixSizeException();
				}
		}
		catch (MatrixSizeException& mex) {
			mex.handle();
		}
	} while (r < band || c<band || r>c);

	//Configuram matricea rezultanta
	construct.setCols(c);
	construct.setRows(r);

	//Construim prima linie
	for (int i = 0; i < band - 1; i++)
		construct.addValue(0, i, 1);

	//Construim ultima linie

	int els = 0;
	for (int i = c - band + 1; i < c; i++) {

		if (i <= c) {
			construct.addValue(r - 1, i, 1);
			els++;
		}
	}

	//Posibilitatea ca numarul de coloane sa fie insuficient pentru introducerea intregii benzi (lungime banda-1) pe ultima linie.
	if (els < band - 1) {
		cout << "Numarul de coloane introdus nu poate permite introducerea intregii benzi pe ultima linie a matricei!\nDoriti sa reincercati? (Y/N)";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			this->bandMatrix();
		}
		else {
			exit(0);
		}
	}

	SMatrix<int>error(0, 0);

	//Construim celelalte linii ramase
	int idx = 0, spacing = 0;
	for (int i = 1; i < r - 1; i++) {
		int contains = 0;
		while (idx < band) {
			if (idx + spacing < c) {
				construct.addValue(i, idx + spacing, 1);
				contains++;
			}
			else {
				cout << "Numarul de coloane introdus nu poate permite introducerea intregii benzi pe una din liniile matricei!\n Matricea nu poate fi randata!\nDoriti sa reincercati? (Y/N)";
				char choice;
				cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					this->bandMatrix();
				}
				else {
					exit(0);
				}
			}
			idx++;
		}

		if (contains != band)
		{
			cout << "Numarul de coloane introdus nu permite afisarea corecta a matricei banda!\nDoriti sa reincercati?";
			return error;
			char choice;
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				this->bandMatrix();
			}
			else {
				exit(0);
			}
		}

		idx = 0;
		spacing++;

	}
	// Daca matricea a putut fi creata cu succes, copiem in obiectul curent rezultatul si il returnam
	*this = construct;

	return *this;

}

